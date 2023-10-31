// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include <stddef.h>  // NULL
#include <stdio.h>   // fprintf, stderr
#include <stdlib.h>  // malloc, realloc
#include <time.h>    // rand

#include "MiniFB.h"
#include "robotsim.h"

#define WINDOW_TITLE "Robot Simulator"

static struct frame ctx = {.width = 800, .height = 600, .buffer = NULL};
static struct scene* scene;
static struct robot predicted_robot;

// resize callback
void resize(struct mfb_window* window, int width, int height) {
    ctx.width = width;
    ctx.height = height;
    ctx.buffer = realloc(ctx.buffer, ctx.width * ctx.height * BYTES_PER_PIXEL);
}

static void robot_move(struct robot* robot, struct scene* scene, double dt) {
    static int iters = 0;
    if (iters % 100 == 0) {
        printf("ground truth: (%f, %f)\n", robot->x, robot->y);
        printf("predicted: (%f, %f)\n", predicted_robot.x, predicted_robot.y);
    }

    predicted_robot = kalman_predict(predicted_robot, dt,
        (struct covariance){0.1, 0, 0.1});
    if (iters > 300) {
        predicted_robot = kalman_update(predicted_robot, *robot,
            (struct covariance){0.1, 0, 0.1});
        printf("updated\n");
        iters = 0;
    }

    iters++;

    // don't move if colliding
    struct object* collision = scene_check_robot_collision(scene);
    if (collision != NULL) {
        collision->color = MFB_RGB(255, 255, 0);
        return;
    }

    // update velocity
    robot->vx += robot->ax * dt;
    robot->vy += robot->ay * dt;

    // update position
    robot->x += robot->vx * dt;
    robot->y += robot->vy * dt;
}

int main() {
    srand(time(NULL));

    // create window
    struct mfb_window* window = mfb_open_ex(WINDOW_TITLE, ctx.width, ctx.height,
        WF_RESIZABLE);
    if (!window) {
        fprintf(stderr, "Failed to open window\n");
        return 1;
    }
    ctx.buffer = malloc(ctx.width * ctx.height * BYTES_PER_PIXEL);

    // configure window
    mfb_set_resize_callback(window, resize);

    // create the scene
    scene = scene_create();
    if (!scene) {
        fprintf(stderr, "Failed to create scene\n");
        return 1;
    }

    // setup the robot
    struct robot* robot = scene_get_robot(scene);
    robot->vy = -10;               // motion up
    robot->ay = -0.1 * robot->vy;  // drag down
    robot_copy(&predicted_robot, robot);

    // add stuff to scene
    // scene_add_rect(scene, -100, -100, 100, 25);
    // scene_add_rect(scene, -100, -100, 25, 100);
    scene_add_rect(scene, 75, -100, 25, 100);
    // scene_add_rect(scene, -100, 75, 100, 25);
    // scene_add_rect(scene, -175, -175, 350, 25);
    // scene_add_rect(scene, -175, 150, 350, 25);
    // scene_add_rect(scene, -175, -150, 25, 300);
    // scene_add_rect(scene, 150, -150, 25, 300);

    // main loop
    mfb_update_state state;
    do {
        // wind force that pushes the robot to the right and varies randomly
        robot->ax = 0.1 + (rand() % 100) / 1000.0;
        robot_move(robot, scene, 1.0 / mfb_get_target_fps());
        scene_draw(scene, &ctx, -robot->x, -robot->y, ctx.width, ctx.height);

        state = mfb_update_ex(window, ctx.buffer, ctx.width, ctx.height);
        if (state != STATE_OK) {
            break;
        }
    } while (mfb_wait_sync(window));

    // clean up resources
    scene_destroy(scene);

    // handle exit state
    switch (state) {
        case STATE_OK:
        case STATE_EXIT:
            return 0;  // exit early on success
        case STATE_INVALID_WINDOW:
            fprintf(stderr, "Invalid window\n");
            break;
        case STATE_INVALID_BUFFER:
            fprintf(stderr, "Invalid buffer\n");
            break;
        case STATE_INTERNAL_ERROR:
            fprintf(stderr, "Internal error\n");
        default:
            fprintf(stderr, "Unknown error: %d\n", state);
            break;
    }
    return 1;
}

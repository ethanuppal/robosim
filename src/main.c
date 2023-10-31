// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include <stddef.h>  // NULL
#include <stdio.h>   // fprintf, stderr
#include <stdlib.h>  // malloc, realloc

#include "MiniFB.h"
#include "robotsim.h"

#define WINDOW_TITLE "Robot Simulator"

static struct frame ctx = {.width = 800, .height = 600, .buffer = NULL};
static struct scene* scene;

// resize callback
void resize(struct mfb_window* window, int width, int height) {
    ctx.width = width;
    ctx.height = height;
    ctx.buffer = realloc(ctx.buffer, ctx.width * ctx.height * BYTES_PER_PIXEL);
}

int main() {
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
    struct robot* robot = scene_get_robot(scene);

    // add stuff to scene
    scene_add_rect(scene, -100, -100, 100, 25);
    scene_add_rect(scene, -100, -100, 25, 100);
    scene_add_rect(scene, 75, -100, 25, 100);
    scene_add_rect(scene, -100, 75, 100, 25);
    scene_add_rect(scene, -175, -175, 350, 25);
    scene_add_rect(scene, -175, 150, 350, 25);
    scene_add_rect(scene, -175, -150, 25, 300);
    scene_add_rect(scene, 150, -150, 25, 300);

    // main loop
    mfb_update_state state;
    do {
        scene_draw(scene, &ctx, -robot->x, -robot->y, ctx.width, ctx.height);

        state = mfb_update_ex(window, ctx.buffer, ctx.width, ctx.height);
        if (state != STATE_OK) {
            break;
        }
    } while (mfb_wait_sync(window));

    // get rid of scene
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

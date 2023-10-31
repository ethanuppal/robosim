// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include "scene.h"

#include <stdlib.h>  // malloc, realloc

#include "MiniFB.h"  // RGB
#include "collide.h"
#include "robot.h"

// well, in case you didn't think this was thread-unsafe already...
static struct object robot_circle_hack;

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

static inline void _init_robot_circle_hack(const struct scene* scene) {
    robot_circle_hack.type = OBJECT_TYPE_CIRCLE;
    robot_circle_hack.value.circle.x = scene->robot.x;
    robot_circle_hack.value.circle.y = scene->robot.y;
    robot_circle_hack.value.circle.radius = scene->robot.radius;
}

struct scene* scene_create() {
    struct scene* scene = malloc(sizeof(*scene));
    if (!scene) {
        return NULL;
    }

    // create the object array
    scene->object_count = 0;
    scene->object_capacity = 10;
    scene->objects = malloc(sizeof(*scene->objects) * scene->object_capacity);
    if (!scene->objects) {
        free(scene);
        return NULL;
    }

    // place the robot at the origin of radius 10
    robot_init(&scene->robot, 0, 0, 0, 0, 0, 0, 10);

    // default fill color is white
    scene->color = MFB_RGB(255, 255, 255);

    return scene;
}

void scene_destroy(struct scene* scene) {
    if (scene) {
        free(scene->objects);
        free(scene);
    }
}

/**
 * @brief Creates a new empty object in the scene with the current fill color of
 * the scene.
 */
static struct object* _scene_new_object(struct scene* scene) {
    // add new object to object array
    if (scene->object_count + 1 >= scene->object_capacity) {
        scene->object_capacity *= 2;
        scene->objects = realloc(scene->objects,
            sizeof(*scene->objects) * scene->object_capacity);
        if (!scene->objects) {
            return NULL;
        }
    }
    struct object** next_ptr = &scene->objects[scene->object_count++];

    // create the object with the current fill color
    struct object* next = malloc(sizeof(*next));
    if (!next) {
        return NULL;
    }
    next->color = scene->color;
    *next_ptr = next;
    return next;
}

struct object* scene_add_line(struct scene* scene, double x1, double y1,
    double x2, double y2) {
    struct object* line = _scene_new_object(scene);
    if (!line) {
        return NULL;
    }

    line->type = OBJECT_TYPE_LINE;
    line->value.line.x1 = x1;
    line->value.line.y1 = y1;
    line->value.line.x2 = x2;
    line->value.line.y2 = y2;

    return line;
}

struct object* scene_add_rect(struct scene* scene, double x, double y, double w,
    double h) {
    struct object* rect = _scene_new_object(scene);
    if (!rect) {
        return NULL;
    }

    rect->type = OBJECT_TYPE_RECT;
    rect->value.rect.x = x;
    rect->value.rect.y = y;
    rect->value.rect.w = w;
    rect->value.rect.h = h;

    return rect;
}

struct object* scene_add_circle(struct scene* scene, double x, double y,
    double radius) {
    struct object* circle = _scene_new_object(scene);
    if (!circle) {
        return NULL;
    }

    circle->type = OBJECT_TYPE_CIRCLE;
    circle->value.circle.x = x;
    circle->value.circle.y = y;
    circle->value.circle.radius = radius;

    return circle;
}

bool scene_remove_object(struct scene* scene, struct object* object) {
    for (size_t i = 0; i < scene->object_count; i++) {
        if (scene->objects[i] == object) {
            scene->objects[i] = scene->objects[scene->object_count - 1];
            scene->object_count--;
            return true;
        }
    }
    return false;
}

/**
 * @brief Scales a value from the scene to the frame.
 * @param w The value to scale in a certain direction.
 * @param view_w The measure of the frame in the scaling direction.
 * @param width The measure of the frame in the scaling direction.
 * @return The scaled value.
 */
static uint32_t _frame_scale(double w, double view_w, uint32_t width) {
    return (uint32_t)(w * width / view_w);
}

/**
 * @brief Translates a value from the scene to the view box.
 * @param x The value to translate in a certain direction.
 * @param trans_x The translation in the direction.
 * @param view_w The measure of the frame in the translation direction.
 * @param width The measure of the frame in the translation direction.
 * @return The translated value.
 */
static uint32_t _vb_trans(double x, double trans_x, double view_w) {
    return x + trans_x + view_w / 2;
}

#include <stdio.h>

void scene_draw(struct scene* scene, struct frame* frame, double trans_x,
    double trans_y, double view_w, double view_h) {
    // clear the frame
    frame_draw_rect(frame, 0, 0, frame->width, frame->height, 0 /* black */);

    // resize viewbox
    double aspect = (double)frame->width / (double)frame->height;
    if (aspect > 1) {
        // if the frame is wider than it is tall, we have to downscale the
        // viewbox's height so the scene isn't distorted
        view_h = view_w / aspect;
    } else {
        // similarly, if the frame is taller than it is wide, we have to
        // downscale the viewbox's width
        view_w = view_h * aspect;
    }

    // draw the objects in the scene

    // (robot circle hack to avoid code duplicating the circle draw code)
    _init_robot_circle_hack(scene);
    robot_circle_hack.color = MFB_RGB(255, 0, 0);

    for (size_t i = 0; i <= scene->object_count; i++) {
        const struct object* object;
        if (i == scene->object_count) {
            object = &robot_circle_hack;
        } else {
            object = scene->objects[i];
        }
        switch (object->type) {
            case OBJECT_TYPE_LINE:

                break;
            case OBJECT_TYPE_RECT: {
                const struct _object_rect* rect = &object->value.rect;

                // translate into view box frame
                double rect_x1 = _vb_trans(rect->x, trans_x, view_w);
                double rect_y1 = _vb_trans(rect->y, trans_y, view_h);
                double rect_x2 = _vb_trans(rect->x + rect->w, trans_x, view_w);
                double rect_y2 = _vb_trans(rect->y + rect->h, trans_y, view_h);

                // check if cut off, if not, bound dimensions
                rect_x1 = max(rect_x1, 0);
                rect_y1 = max(rect_y1, 0);
                rect_x2 = min(rect_x2, view_w);
                rect_y2 = min(rect_y2, view_h);
                if (rect_x1 >= rect_x2 || rect_y1 >= rect_y2) {
                    continue;
                }

                // convert to pixels
                uint32_t x1 = _frame_scale(rect_x1, view_w, frame->width);
                uint32_t y1 = _frame_scale(rect_y1, view_h, frame->height);
                uint32_t x2 = _frame_scale(rect_x2, view_w, frame->width);
                uint32_t y2 = _frame_scale(rect_y2, view_h, frame->height);

                // draw the rect
                frame_draw_rect(frame, x1, y1, x2, y2, object->color);

                break;
            }
            case OBJECT_TYPE_CIRCLE: {
                const struct _object_circle* circle = &object->value.circle;

                // translate into view box frame
                double circ_x = _vb_trans(circle->x, trans_x, view_w);
                double circ_y = _vb_trans(circle->y, trans_y, view_h);

                // check if cut off (thankfully dimension gets bounded for us)
                if (circ_x + circle->radius < 0 || circ_y + circle->radius < 0
                    || circ_x - circle->radius > view_w
                    || circ_y - circle->radius > view_h) {
                    continue;
                }

                // convert to pixels
                uint32_t x = _frame_scale(circ_x, view_w, frame->width);
                uint32_t y = _frame_scale(circ_y, view_h, frame->height);
                uint32_t radius = _frame_scale(circle->radius, view_w,
                    frame->width);

                // draw the circle
                frame_draw_circle(frame, x, y, radius, object->color);

                break;
            }
        }
    }
}

struct robot* scene_get_robot(struct scene* scene) {
    return &scene->robot;
}

struct object* scene_check_robot_collision(struct scene* scene) {
    _init_robot_circle_hack(scene);
    for (size_t i = 0; i < scene->object_count; ++i) {
        struct object* object = scene->objects[i];
        if (objects_collide(&robot_circle_hack, object)) {
            return object;
        }
    }
    return NULL;
}

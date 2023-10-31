// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include "collide.h"

#include <math.h>  // fabs

// my < vs <= conventions are all screwed up LOL

static bool _rects_collide(struct _object_rect* a, struct _object_rect* b) {
    // simply checks if there is an overlapping region
    return (a->x < b->x + b->w) && (a->y < b->y + b->w) && (a->x + a->w > b->x)
           && (a->y + a->h > b->y);
}

static bool _circles_collide(struct _object_circle* a,
    struct _object_circle* b) {
    // checks if distance between centers < a->radius + b->radius
    int32_t dx = (int32_t)a->x - (int32_t)b->x;
    int32_t dy = (int32_t)a->y - (int32_t)b->y;
    return dx * dx + dy * dy
           < (a->radius + b->radius) * (a->radius + b->radius);
}

static bool _rect_circle_collide(struct _object_rect* a,
    struct _object_circle* b) {
    // 1. check if center is in rect
    if ((b->x >= a->x) && (b->x <= a->x + a->w) && (b->y >= a->y)
        && (b->y <= a->y + a->h)) {
        return true;
    }

    // 2. check if distance (horizontal or vertical) to closest side is < R
    double dist_to_left = b->x - a->x;
    double dist_to_right = b->x - (a->x + a->w);
    double dist_to_top = b->y - a->y;
    double dist_to_bottom = b->y - a->y - a->h;
    if (b->x <= a->x) {
        // circle is to the left of the rect
        // check distance to left side
        if (dist_to_left <= b->radius && b->y >= a->y && b->y <= a->y + a->h) {
            return true;
        }
        // check distance to top left corner
        if (dist_to_left * dist_to_left + dist_to_top * dist_to_top
            <= b->radius * b->radius) {
            return true;
        }
        // check distance to bottom left corner
        if (dist_to_left * dist_to_left + dist_to_bottom * dist_to_bottom
            <= b->radius * b->radius) {
            return true;
        }
    } else if (b->x >= a->x + a->w) {
        // circle is to the right of the rect
        // check distance to right side
        if (dist_to_right <= b->radius && b->y >= a->y && b->y <= a->y + a->h) {
            return true;
        }
        // check distance to top right corner
        if (dist_to_right * dist_to_right + dist_to_right * dist_to_right
            < b->radius * b->radius) {
            return true;
        }
        // check distance to bottom right corner
        if (dist_to_right * dist_to_right + dist_to_bottom * dist_to_bottom
            < b->radius * b->radius) {
            return true;
        }
    } else {
        // circle is in the middle of the rect
        return fabs(dist_to_top) <= b->radius
               || fabs(dist_to_bottom) <= b->radius;
    }

    return false;
}

bool objects_collide(struct object* a, struct object* b) {
    switch (a->type) {
        case OBJECT_TYPE_RECT:
            switch (b->type) {
                case OBJECT_TYPE_RECT:
                    return _rects_collide(&a->value.rect, &b->value.rect);
                case OBJECT_TYPE_CIRCLE:
                    return _rect_circle_collide(&a->value.rect,
                        &b->value.circle);
            }
        case OBJECT_TYPE_CIRCLE:
            switch (b->type) {
                case OBJECT_TYPE_RECT:
                    return _rect_circle_collide(&b->value.rect,
                        &a->value.circle);
                case OBJECT_TYPE_CIRCLE:
                    return _circles_collide(&a->value.circle, &b->value.circle);
            }
    }
}

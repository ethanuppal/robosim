// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include <stdbool.h>

#include "scene.h"

/**
 * @brief Check if two objects collide.
 *
 * @param a The first object.
 * @param b The second object.
 * @return `true` if the objects collide, `false` otherwise.
 * @pre `a` and `b` are not `NULL`.
 */
bool objects_collide(struct object* a, struct object* b);

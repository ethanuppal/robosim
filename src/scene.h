// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#pragma once

#include <stdbool.h>  // bool
#include <stddef.h>   // size_t

#include "frame.h"
#include "robot.h"

/**
 * @brief An object in the scene.
 */
struct object {
    enum object_type {
        OBJECT_TYPE_LINE,   ///< A line segment.
        OBJECT_TYPE_RECT,   ///< A rectangle.
        OBJECT_TYPE_CIRCLE  ///< A circle.
    } type;                 ///< The geometric type of object.

    union {
        struct _object_line {
            double x1;      ///< The x-coordinate of the first point.
            double y1;      ///< The y-coordinate of the first point.
            double x2;      ///< The x-coordinate of the second point.
            double y2;      ///< The y-coordinate of the second point.
        } line;
        struct _object_rect {
            double x;       ///< The x-coordinate of the top left corner.
            double y;       ///< The y-coordinate of the top left corner.
            double w;       ///< The width of the rectangle.
            double h;       ///< The height of the rectangle.
        } rect;
        struct _object_circle {
            double x;       ///< The x-coordinate of the center.
            double y;       ///< The y-coordinate of the center.
            double radius;  ///< The radius of the circle.
        } circle;
    } value;                ///< The geometric data of the object.

    uint32_t color;         ///< The fill color of the object.
};

/**
 * @brief A scene containing objects and a robot.
 */
struct scene {
    struct object** objects;  ///< The objects in the scene.
    size_t object_count;      ///< The number of objects in the scene.
    size_t object_capacity;   ///< The capacity of the objects array.
    struct robot robot;       ///< The robot in the scene.
    uint32_t color;           ///< The current filll color of the scene.
};

/**
 * @brief Creates a new scene with no objects and a robot centered at the
 * origin. The default fill color is white.
 * @return The new scene or NULL on error.
 * @note The scene must be destroyed with `scene_destroy()`.
 * @see scene_destroy()
 * @see struct scene
 * @see struct object
 * @see struct robot
 * @code
 * // Create a new scene.
 * struct scene *scene = scene_create();
 * if (!scene) {
 *    // Handle error.
 * }
 * @endcode
 */
struct scene* scene_create(void);

/**
 * @brief Frees all resources associated with the scene.
 * If `scene` is NULL, this function has no effect.
 * @param scene The scene to destroy.
 * @see scene_create()
 * @see struct scene
 * @code
 * // Destroy the scene.
 * scene_destroy(scene);
 * @endcode
 */
void scene_destroy(struct scene* scene);

/**
 * @brief Adds a line segment to the scene.
 * @param scene The scene to add the line to.
 * @param x1 The x-coordinate of the first point.
 * @param y1 The y-coordinate of the first point.
 * @param x2 The x-coordinate of the second point.
 * @param y2 The y-coordinate of the second point.
 * @return The new object or NULL on error.
 */
struct object* scene_add_line(struct scene* scene, double x1, double y1,
    double x2, double y2);

/**
 * @brief Adds a rectangle to the scene.
 * @param scene The scene to add the rectangle to.
 * @param x The x-coordinate of the top left corner.
 * @param y The y-coordinate of the top left corner.
 * @param w The width of the rectangle.
 * @param h The height of the rectangle.
 * @return The new object or NULL on error.
 */
struct object* scene_add_rect(struct scene* scene, double x, double y, double w,
    double h);

/**
 * @brief Adds a circle to the scene.
 * @param scene The scene to add the circle to.
 * @param x The x-coordinate of the center.
 * @param y The y-coordinate of the center.
 * @param r The radius of the circle.
 * @return The new object or NULL on error.
 */
struct object* scene_add_circle(struct scene* scene, double x, double y,
    double r);

/**
 * @brief Removes an object from the scene.
 * @param scene The scene to remove the object from.
 * @param object The object to remove.
 * @return True if the object was removed, false if it was not found.
 */
bool scene_remove_object(struct scene* scene, struct object* object);

/**
 * @brief Draws the scene to the frame.
 * Note that the actual viewbox dimensions may be adjusted to fit the frame.
 * @param scene The scene to draw.
 * @param frame The frame to draw to.
 * @param trans_x The x translation of the view box.
 * @param trans_y The y translation of the view box.
 * @param view_w The width of the intended view box.
 * @param view_h The height of the intended view box.
 * @pre `scene` and `frame` are not NULL.
 * @pre `view_w` and `view_h` are greater than 0.
 */
void scene_draw(struct scene* scene, struct frame* frame, double trans_x,
    double trans_y, double view_w, double view_h);

/**
 * @brief Retrieves a handle for the robot in the scene.
 * Only valid for as long as the scene is in memory.
 * @param scene The scene to get the robot from.
 * @return The robot in the scene.
 */
struct robot* scene_get_robot(struct scene* scene);

/**
 * @brief Checks if the robot is colliding with any objects in the scene.
 * @param scene The scene to check.
 * @return The object the robot is colliding with, or NULL if it is not.
 */
struct object* scene_check_robot_collision(struct scene* scene);

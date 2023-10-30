// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#pragma once

#include <stddef.h>  // NULL
#include <stdint.h>  // uint32_t

#define BYTES_PER_PIXEL 4

/**
 * @brief A frame containing a buffer of 32-bit pixels.
 */
struct frame {
    uint32_t width;
    uint32_t height;
    uint32_t* buffer;
};

/**
 * @brief Draws a line on the frame using Bresenham's line algorithm.
 * @param frame The frame to draw on.
 * @param x1 The x coordinate of the first point.
 * @param y1 The y coordinate of the first point.
 * @param x2 The x coordinate of the second point.
 * @param y2 The y coordinate of the second point.
 * @param color The color of the line.
 */
void frame_draw_line(struct frame* frame, uint32_t x1, uint32_t y1, uint32_t x2,
    uint32_t y2, uint32_t color);

/**
 * @brief Draws a rectangle on the frame.
 * Assumes that the rectangle fits within the bounds of `frame`.
 * @param frame The frame to draw on.
 * @param x1 The x coordinate of the top left corner.
 * @param y2 The y coordinate of the top left corner.
 * @param x2 The x coordinate of the bottom right corner.
 * @param y2 The y coordinate of the bottom right corner.
 * @param color The color of the rectangle.
 */
void frame_draw_rect(struct frame* frame, uint32_t x1, uint32_t y1, uint32_t x2,
    uint32_t y2, uint32_t color);

/**
 * @brief Draws a circle on the frame.
 * @param frame The frame to draw on.
 * @param x The x coordinate of the center.
 * @param y The y coordinate of the center.
 * @param radius The radius of the circle.
 * @param color The color of the circle.
 */
void frame_draw_circle(struct frame* frame, uint32_t x, uint32_t y,
    uint32_t radius, uint32_t color);

// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include "frame.h"

#include <stdio.h>
#include <stdlib.h>

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

void frame_draw_line(struct frame* frame, uint32_t x1, uint32_t y1, uint32_t x2,
                     uint32_t y2, uint32_t color) {
    fprintf(stderr, "frame_draw_line: not implemented\n");
    exit(1);
}

void frame_draw_rect(struct frame* frame, uint32_t x1, uint32_t y1, uint32_t x2,
                     uint32_t y2, uint32_t color) {
    for (uint32_t y = y1; y < y2; y++) {
        for (uint32_t x = x1; x < x2; x++) {
            frame->buffer[y * frame->width + x] = color;
        }
    }
}

void frame_draw_circle(struct frame* frame, uint32_t x, uint32_t y,
                       uint32_t radius, uint32_t color) {
    // TODO: use a better drawing algorithm
    uint32_t x1 = max(x - radius, 0);
    uint32_t y1 = max(y - radius, 0);
    uint32_t x2 = min(x + radius, frame->width - 1);
    uint32_t y2 = min(y + radius, frame->height - 1);
    printf("x1: %u, y1: %u, x2: %u, y2: %u\n", x1, y1, x2, y2);
    for (uint32_t y = y1; y < y2; y++) {
        for (uint32_t x = x1; x < x2; x++) {
            if ((x - x1) * (x - x1) + (y - y1) * (y - y1) <= radius * radius) {
                frame->buffer[y * frame->width + x] = color;
            }
        }
    }
}

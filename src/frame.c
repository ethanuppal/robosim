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

uint32_t _norm_sq(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
    int32_t dx = (int32_t)x1 - (int32_t)x2;
    int32_t dy = (int32_t)y1 - (int32_t)y2;
    return dx * dx + dy * dy;
}

void frame_draw_circle(struct frame* frame, uint32_t x, uint32_t y,
    uint32_t radius, uint32_t color) {
    // TODO: use a better drawing algorithm
    uint32_t x1 = max(x - radius, 0);
    uint32_t y1 = max(y - radius, 0);
    uint32_t x2 = min(x + radius, frame->width - 1);
    uint32_t y2 = min(y + radius, frame->height - 1);
    for (uint32_t j = y1; j < y2; j++) {
        for (uint32_t i = x1; i < x2; i++) {
            if (_norm_sq(i, j, x, y) <= radius * radius) {
                frame->buffer[j * frame->width + i] = color;
            }
        }
    }
}

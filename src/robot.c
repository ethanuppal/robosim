// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include "robot.h"

void robot_init(struct robot* robot, double x, double y, double vx, double vy,
    double ax, double ay, double radius) {
    robot->x = x;
    robot->y = y;
    robot->vx = vx;
    robot->vy = vy;
    robot->ax = ax;
    robot->ay = ay;
    robot->radius = radius;
    robot->cov.cov_xx = 0;
    robot->cov.cov_xy = 0;
    robot->cov.cov_yy = 0;
}

void robot_copy(struct robot* dest, const struct robot* src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->vx = src->vx;
    dest->vy = src->vy;
    dest->ax = src->ax;
    dest->ay = src->ay;
    dest->radius = src->radius;
    dest->cov.cov_xx = src->cov.cov_xx;
    dest->cov.cov_xy = src->cov.cov_xy;
    dest->cov.cov_yy = src->cov.cov_yy;
}

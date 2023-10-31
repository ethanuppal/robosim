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

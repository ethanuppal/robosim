// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include "robot.h"

void robot_init(struct robot* robot, double x, double y, double radius,
    double velocity, double accel, double heading) {
    robot->x = x;
    robot->y = y;
    robot->radius = radius;
    robot->velocity = velocity;
    robot->accel = accel;
    robot->heading = heading;
}

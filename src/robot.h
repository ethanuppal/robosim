// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#pragma once

#include "covariance.h"

/**
 * @brief A robot represented by a point in space with heading.
 */
struct robot {
    double x;               ///< The x-coordinate of the robot.
    double y;               ///< The y-coordinate of the robot.
    double vx;              ///< The x-velocity of the robot.
    double vy;              ///< The y-velocity of the robot.
    double ax;              ///< The x-acceleration of the robot.
    double ay;              ///< The y-acceleration of the robot.
    double radius;          ///< The radius of the robot.
    struct covariance cov;  ///< The uncertainty in the robot's state.
};

/**
 * @brief Initializes a robot.
 * @param robot The robot to initialize.
 * @param x The x-coordinate of the robot.
 * @param y The y-coordinate of the robot.
 * @param vx The x-velocity of the robot.
 * @param vy The y-velocity of the robot.
 * @param radius The radius of the robot.
 * @pre `robot` is not NULL.
 */
void robot_init(struct robot* robot, double x, double y, double vx, double vy,
    double ax, double ay, double radius);

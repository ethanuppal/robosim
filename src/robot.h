// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#pragma once

/**
 * @brief A robot represented by a point in space with heading.
 */
struct robot {
    double x;         ///< The x coordinate of the robot.
    double y;         ///< The y coordinate of the robot.
    double radius;    ///< The radius of the robot.
    double velocity;  ///< The velocity of the robot.
    double accel;     ///< The acceleration of the robot.
    double heading;   ///< The heading of the robot.
};

/**
 * @brief Initializes a robot.
 * @param robot The robot to initialize.
 * @param x The x coordinate of the robot.
 * @param y The y coordinate of the robot.
 * @param radius The radius of the robot.
 * @param velocity The velocity of the robot.
 * @param accel The acceleration of the robot.
 * @param heading The heading of the robot.
 * @pre `robot` is not NULL.
 */
void robot_init(struct robot* robot, double x, double y, double radius,
    double velocity, double accel, double heading);

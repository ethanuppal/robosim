// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#pragma once

#include "robot.h"
#include "sensor.h"

/**
 * @brief Predicts the next state of the robot.
 * @param robot The robot to predict the next state of.
 * @param dt The time since the last prediction.
 * @param noise The external noise.
 * @return The predicted state of the robot.
 */
struct robot kalman_predict(struct robot robot, double dt,
    struct covariance noise);

/**
 * @brief Updates the state of the robot based on the sensor data.
 * @param robot The robot to update the state of.
 * @param sensor_result The result of the sensor.
 * @param sensor_noise The noise of the sensor.
 * @return The updated state of the robot.
 */
struct robot kalman_update(struct robot robot, struct robot sensor_result,
    struct covariance sensor_noise);

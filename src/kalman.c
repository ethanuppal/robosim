// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include "kalman.h"

struct robot kalman_predict(struct robot robot, double dt,
    struct covariance noise) {
    // update position with kinematics
    robot.x += robot.vx * dt + 0.5 * robot.ax * dt * dt;
    robot.y += robot.vy * dt + 0.5 * robot.ay * dt * dt;
    robot.vx += robot.ax * dt;
    robot.vy += robot.ay * dt;

    // update covariance matrix with external noise
    robot.cov.cov_xx += noise.cov_xx;
    robot.cov.cov_xy += noise.cov_xy;
    robot.cov.cov_yy += noise.cov_yy;

    return robot;
}

// these equations literally stolen fromm
// https://www.bzarg.com/p/how-a-kalman-filter-works-in-pictures/#mjx-eqn-matrixupdate
struct robot kalman_update(struct robot robot, struct robot sensor_result,
    struct covariance sensor_noise) {
    double kalman_gain_x = robot.cov.cov_xx
                           / (robot.cov.cov_xx + sensor_noise.cov_xx);
    double kalman_gain_y = robot.cov.cov_yy
                           / (robot.cov.cov_yy + sensor_noise.cov_yy);

    robot.x = robot.x + kalman_gain_x * (sensor_result.x - robot.x);
    robot.y = robot.y + kalman_gain_y * (sensor_result.y - robot.y);
    robot.vx = robot.vx + kalman_gain_x * (sensor_result.vx - robot.vx);
    robot.vy = robot.vy + kalman_gain_y * (sensor_result.vy - robot.vy);

    // update covariance matrix for the new state
    robot.cov.cov_xx = (1 - kalman_gain_x) * robot.cov.cov_xx;
    robot.cov.cov_xy = (1 - kalman_gain_x) * robot.cov.cov_xy;
    robot.cov.cov_yy = (1 - kalman_gain_y) * robot.cov.cov_yy;

    return robot;
}

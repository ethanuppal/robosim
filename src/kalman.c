// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include "kalman.h"

struct robot kalman_predict(struct robot robot, double dt,
    struct covariance noise) {
    // update position with kinematics
    robot.x += robot.vx * dt;
    robot.y += robot.vy * dt;

    // update covariance matrix with external noise
    robot.cov.cov_xx += noise.cov_xx;
    robot.cov.cov_xy += noise.cov_xy;
    robot.cov.cov_yy += noise.cov_yy;

    return robot;
}

struct robot kalman_update(struct robot robot, struct robot sensor_result,
    struct covariance sensor_noise) {
}

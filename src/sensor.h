// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#pragma once

#include <stddef.h>
#include "scene.h'
#include "robot.h"

/**
 * @brief Represents a covariance matrix by its eigenvectors.
 */
struct covariance {
    size_t eigenvectors_count;  ///< The number of eigenvectors. Invariant:
                                ///< eigenvectors_count is a multiple of 2.
    double* eigenvectors;       ///< The eigenvectors.
};

struct sensor_result {
    struct covariance cov;  ///< The covariance matrix of the sensor.
    double* data;           ///< The measurements of the sensor.
};

typedef struct sensor_result (*sensor_func)(struct robot* robot,
    struct scene* scene);

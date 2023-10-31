// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#pragma once

/**
 * @brief Represents a covariance matrix.
 */
struct covariance {
    double cov_xx;  ///< The variance of the x-coordinate.
    double cov_xy;  ///< The covariance of the x- and y-coordinates.
    double cov_yy;  ///< The variance of the y-coordinate.
};

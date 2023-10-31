// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#pragma once

#include <stddef.h>

#include "robot.h"
#include "scene.h"

typedef struct robot (*sensor_func)(struct robot* robot, struct scene* scene);

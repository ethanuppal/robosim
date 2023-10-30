#!/bin/bash
# Copyrigth (C) 2023 Ethan Uppal. All rights reserved.

find src/ -iname *.h -o -iname *.c | xargs clang-format -i

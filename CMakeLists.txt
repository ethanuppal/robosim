# CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(robosim)

add_executable(${PROJECT_NAME}
    src/main.c
    src/robotsim.h
    src/scene.c src/scene.h
    src/frame.c src/frame.h
    src/collide.c src/collide.h
    src/robot.c src/robot.h
    src/sensor.c src/sensor.h
    src/kalman.c src/kalman.h)

add_subdirectory(dependencies/minifb)

# Link MiniFB to your project:
target_link_libraries(${PROJECT_NAME}
    minifb
)

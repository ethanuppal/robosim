# CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(robotsim)
add_executable(${PROJECT_NAME} src/main.c)

add_subdirectory(dependencies/minifb)

# Link MiniFB to your project:
target_link_libraries(${PROJECT_NAME}
    minifb
)

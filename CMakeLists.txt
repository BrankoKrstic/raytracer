cmake_minimum_required(VERSION 3.30)
project(raytracer)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} raytracerlib)

add_subdirectory(lib)
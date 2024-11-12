cmake_minimum_required(VERSION 3.5.0)
project(8-puzzle VERSION 0.1.0)

add_executable(8-puzzle src/field.cpp src/main.cpp)
target_include_directories(8-puzzle PRIVATE include)
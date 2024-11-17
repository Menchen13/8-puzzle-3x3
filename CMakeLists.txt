cmake_minimum_required(VERSION 3.5.0)
project(8-puzzle VERSION 0.1.0)

file(GLOB SRC_FILES src/*.cpp)

add_executable(8-puzzle ${SRC_FILES})
target_include_directories(8-puzzle PRIVATE include)
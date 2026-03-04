cmake_minimum_required(VERSION 3.27)
project(CCSDSLab)

set(CMAKE_CXX_STANDARD 17)

add_executable(CCSDSLab src/main.cpp)
target_include_directories(CCSDSLab PRIVATE include)


cmake_minimum_required(VERSION 2.8)
project(sample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wfatal-errors -fPIC")

include_directories(./include)

add_executable(sample sample.cpp)


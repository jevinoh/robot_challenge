cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_STANDARD 14)

project (robot_challenge)

add_executable(robot_challenge robot_challenge.cpp InputParser.cpp TableController.cpp Robot.cpp)

cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_STANDARD 14)

project (robot_challenge)
include_directories(../)
add_executable(test_robot_challenge test_robot_challenge.cpp
                                    ../InputParser.cpp
                                    ../TableController.cpp
                                    ../Robot.cpp)

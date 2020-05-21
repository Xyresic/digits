cmake_minimum_required(VERSION 3.16)
project(digits)

set(CMAKE_CXX_STANDARD 20)

add_executable(digits c++/main.cpp c++/Node.cpp c++/Node.h)
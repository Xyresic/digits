#Assumes the user already has CMake installed
cmake_minimum_required(VERSION 3.16)
project(digits)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

add_executable(digits c++/main.cpp c++/App-Classes/App.cpp c++/App-Classes/App.h c++/App-Classes/Frame.cpp c++/App-Classes/Frame.h c++/App-Classes/DrawPane.cpp c++/App-Classes/DrawPane.h c++/Node.cpp c++/Node.h)

target_link_libraries(digits ${wxWidgets_LIBRARIES})

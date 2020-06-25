cmake_minimum_required(VERSION 3.16)
project(digits)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

add_executable(digits c++/main.cpp c++/wxClasses/App.cpp c++/wxClasses/App.h c++/wxClasses/Frame.cpp c++/wxClasses/Frame.h c++/wxClasses/DrawPane.cpp c++/wxClasses/DrawPane.h c++/Node.cpp c++/Node.h)

target_link_libraries(digits ${wxWidgets_LIBRARIES})

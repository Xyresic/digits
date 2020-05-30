cmake_minimum_required(VERSION 3.16)
project(digits)

set(CMAKE_CXX_STANDARD 20)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

add_executable(digits main.cpp App.cpp App.h Frame.cpp Frame.h DrawPane.cpp DrawPane.h)

target_link_libraries(digits ${wxWidgets_LIBRARIES})
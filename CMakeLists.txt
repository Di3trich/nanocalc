cmake_minimum_required(VERSION 3.8)
project(nanocalc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp nano_window.hpp calc.hpp resource.hpp)
add_executable(nanocalc WIN32 ${SOURCE_FILES})

cmake_minimum_required(VERSION 3.15)
project(lab_11)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(lab_11
        include/bin_manip.h
        include/employees.h
        src/bin_manip.cpp
        src/employees.cpp
        src/main.cpp
        Makefile)

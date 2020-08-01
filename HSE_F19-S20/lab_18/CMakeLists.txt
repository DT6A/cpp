cmake_minimum_required(VERSION 3.15)
project(lab_18)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(lab_18
        include/format.hpp
        src/doctest_main.cpp
        src/smoke_test.cpp
        Makefile)

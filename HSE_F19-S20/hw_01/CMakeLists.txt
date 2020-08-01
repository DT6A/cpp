cmake_minimum_required(VERSION 3.15)
project(hw_01)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(hw_01
        include/bmp.h
        include/error.h
        include/stego.h
        src/bmp.c
        src/main.c
        src/stego.c
        Makefile)

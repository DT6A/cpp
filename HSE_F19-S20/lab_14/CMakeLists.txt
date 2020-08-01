cmake_minimum_required(VERSION 3.10)
project(lab_14)

include_directories(include)

add_compile_options(-Wall -Wextra -Werror)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -g")

set(CMAKE_CXX_STANDARD 14)

add_executable(lab_14 src/main.cpp src/matrix.cpp include/matrix.h)
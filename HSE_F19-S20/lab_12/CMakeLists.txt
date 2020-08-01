cmake_minimum_required(VERSION 3.10)
project(lab_12)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_compile_options(-Wall -Wextra -Werror)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -g")

add_executable(lab_12 src/main.cpp include/my_vector.h include/my_vector_impl.h)

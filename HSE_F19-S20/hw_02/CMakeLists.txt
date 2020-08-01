cmake_minimum_required(VERSION 3.10)
project(hw_02)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_compile_options(-Wall -Wextra -Werror)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -g")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(hw_02
        Makefile include/Board.h src/Board.cpp src/main.cpp src/StdioBoardView.cpp include/StdioBoardView.h include/BoardView.h src/BoardView.cpp src/NcursesBoardView.cpp include/NcursesBoardView.h src/GameController.cpp include/GameController.h include/GameController.h)
target_link_libraries(hw_02 ${CURSES_LIBRARIES})

add_executable(test_hw02
        #EXCLUDE_FROM_ALL
        Makefile include/Board.h include/BoardTest.h src/Board.cpp  test/BoardTest.cpp include/Test.h src/Test.cpp test/test.cpp)

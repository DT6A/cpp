cmake_minimum_required(VERSION 3.10)
project(hw_03)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_compile_options(-Wold-style-cast -Wall -Wextra -Werror)

### Disabled to increase speed ###
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -g")

set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

add_executable(hw_03 src/main.cpp src/HuffmanTree.cpp include/HuffmanTree.h src/HuffmanArchiver.cpp include/HuffmanArchiver.h src/CLI.cpp include/CLI.h src/HuffmanExceptions.cpp include/HuffmanExceptions.h src/StreamManips.cpp include/StreamManips.h)
add_executable(test_hw_03 src/HuffmanTree.cpp include/HuffmanTree.h src/HuffmanArchiver.cpp include/HuffmanArchiver.h src/CLI.cpp include/CLI.h src/HuffmanExceptions.cpp include/HuffmanExceptions.h test/TestMain.cpp test/TestTree.cpp test/TestArchiver.cpp src/StreamManips.cpp include/StreamManips.h test/TestManips.cpp test/TestCLI.cpp)
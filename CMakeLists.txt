cmake_minimum_required (VERSION 3.0)
project (GBA CXX)

add_compile_options (-Wfatal-errors -Wall -Wextra -Wpedantic -Werror -Og)
find_package (GTest REQUIRED)
find_package (Threads REQUIRED)
include_directories (${GTEST_INCLUDE_DIRS})

include_directories (${CMAKETEST_SOURCE_DIR}/include)

add_executable (gba src/Cpu.cpp src/main.cpp src/Memory.cpp src/opcodes.cpp)

add_executable (unitTest src/test/test.cpp src/test/Cpu-test.cpp src/Cpu.cpp src/opcodes.cpp src/Memory.cpp)
target_link_libraries (unitTest gtest gtest_main pthread)
cmake_minimum_required (VERSION 3.0)
project (GBA CXX)

add_compile_options (-Wall -Wextra -Wpedantic -Werror -Og)

include_directories (${CMAKETEST_SOURCE_DIR}/include)

add_executable (gba src/Cpu.cpp src/main.cpp src/Memory.cpp src/opcodes.cpp)
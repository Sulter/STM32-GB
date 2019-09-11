cmake_minimum_required (VERSION 2.6)
project (CMAKETEST C CXX)

include_directories(${CMAKETEST_SOURCE_DIR}/include)

add_executable(gba src/Cpu.cpp src/main.cpp src/Memory.cpp src/opcodes.cpp)
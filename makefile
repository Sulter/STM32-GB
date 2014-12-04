#our objects
OBJS = src/main.cpp src/Cpu.cpp src/opcodes.cpp src/Memory.cpp
#compiler
CC = g++
#flags
COMPILER_FLAGS = -Wall -std=c++11
#external
LINKER_FLAGS = 
#executable
OBJ_NAME = gba

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -rf $(OBJ_NAME)	

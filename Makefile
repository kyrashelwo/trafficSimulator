# Declaration of variables
#
# TODO: 
#	1. auto tracking of header files:
# 	http://stackoverflow.com/questions/2394609/makefile-header-dependencies
# 	2. objects in seperate folder.

CC = g++ 
CC_FLAGS = -Wall -std=c++11
EXEC = carSimulation

# File names
SOURCES = $(wildcard libs/*.cpp *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_DEBUG = $(SOURCES:.cpp=.o_d)

# Main target
compile: $(OBJECTS) 
	$(CC) $(CC_FLAGS) $(OBJECTS) -o $(EXEC)

# debugger
debug: $(OBJECTS_DEBUG)
	$(CC) $(CC_FLAGS) -g $(OBJECTS_DEBUG) -o $(EXEC)

# To obtain object files (only from .cpp)
%.o: %.cpp 
	$(CC) $(CC_FLAGS) -c $< -o $@

# To obtain object files with debug information (only from .cpp)
%.o_d: %.cpp 
	$(CC) $(CC_FLAGS) -g -c $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC)
	rm -f *.o 
	rm -f libs/*.o
	rm -f *.o_d 
	rm -f libs/*.o_d

open:
	vim *.cpp libs/*.cpp libs/*.hpp -p

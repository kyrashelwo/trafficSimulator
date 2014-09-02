# Declaration of variables
#
# TODO: 
#	1. auto tracking of header files:
# 	http://stackoverflow.com/questions/2394609/makefile-header-dependencies
# 	2. objects in seperate folder.

CC = g++ 
SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include
CXX_FLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDF_FLAGS = $(SDL_LIB)
EXEC = trafficSimulator

# File names
SOURCES = $(wildcard libs/*.cpp *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_DEBUG = $(SOURCES:.cpp=.o_d)

# Main target
compile: $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDF_FLAGS) -o $(EXEC)

# debugger
debug: $(OBJECTS_DEBUG)
	$(CC) -g $(OBJECTS_DEBUG) $(LDF_FLAGS) -o $(EXEC)
	gdb $(EXEC)

# To obtain object files (only from .cpp)
%.o: %.cpp 
	$(CC) $(CXX_FLAGS) -c $< -o $@

# To obtain object files with debug information (only from .cpp)
%.o_d: %.cpp 
	$(CC) $(CXX_FLAGS) -g -c $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC)
	rm -f *.o 
	rm -f libs/*.o
	rm -f *.o_d 
	rm -f libs/*.o_d

open:
	vim *.cpp libs/*.cpp libs/*.hpp -p

run:
	./$(EXEC) 2 100 1

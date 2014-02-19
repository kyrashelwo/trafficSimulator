# Declaration of variables
CC = g++ 
CC_FLAGS = -Wall -std=c++11 -g
EXEC = carSimulation

# File names
SOURCES = $(wildcard *.cpp|libs/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
compile: $(OBJECTS) 
	$(CC) $(CC_FLAGS) $(OBJECTS) -o $(EXEC)

# debugger
debug: $(OBJECTS)
	$(CC) $(CC_FLAGS) -g $(OBJECTS) -o $(EXEC)

# To obtain object files (only from .cpp)
%.o: %.cpp 
	$(CC) $(CC_FLAGS) -c $< -o $@


# To remove generated files
clean:
	rm -f $(EXEC)
	rm -f *.o 

test:
	echo $(SOURCES)

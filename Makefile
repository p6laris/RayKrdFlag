# Compiler
CC = gcc

# Source and output files
SRC = main.c
TARGET = kurdistan_flag

# Raylib libraries and dependencies
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -DUSE_WAYLAND_DISPLAY=TRUE

# Default target: compile the program
all:
	$(CC) $(SRC) -o $(TARGET) $(LIBS)

# Run the application
run: all
	./$(TARGET)  # Execute the compiled program

# Clean the generated files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean run

# Makefile for compiling Raylib on macOS

CC = clang
CFLAGS = -Wall -g -std=c99
LDFLAGS = -lraylib -lm -lpthread -ldl -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

SRC = main.c quadtree.c
OBJ = $(SRC:.c=.o)
EXEC = a.out

RAYLIB_PATH = /Users/parry/raylib/src
LIBRARY_PATH = /Users/parry/raylib/src

# The default target to build
all: $(EXEC)

# Compile the source code into an object file
%.o: %.c
	$(CC) $(CFLAGS) -I$(RAYLIB_PATH) -c $< -o $@

# Link the object file(s) into the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ)  -L$(LIBRARY_PATH) $(LDFLAGS) -o $(EXEC)

# Clean the build directory
clean:
	rm -f $(OBJ) $(EXEC)

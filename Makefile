# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

# Target executable
TARGET = kvm

# Source files
SRC = alu.c core.c function.c io.c jmp.c loader.c mem.c other.c
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# Declare phony targets
.PHONY: all clean
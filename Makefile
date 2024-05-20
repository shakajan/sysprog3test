CC = gcc
CFLAGS = -fno-builtin

# Specify the target executable and source file
TARGET = test
SRC = main.c

# Default target
all: $(TARGET)

# Compile the source file into the target executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Clean up intermediate files and the executable
clean:
	rm -f $(TARGET)
CC = gcc
CFLAGS = -fno-builtin

# Specify the target executable and source file
TARGET = test
SRC = main.c

# Default target
all: $(TARGET) create_test11

# Compile the source file into the target executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

create_test11:
	echo 012345678901234567890123456789 > test11

# Clean up intermediate files and the executable
clean:
	rm -f $(TARGET) test*

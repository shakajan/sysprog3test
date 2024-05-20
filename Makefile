CC = gcc
CFLAGS = -fno-builtin

# Specify the target executable and source file
TARGET = test_custom
SRC = test_custom.c

custom: $(TARGET) create_test11

# Compile the source file into the target executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(SRC): main.c
	echo '#include "dbg.h"' > test_custom.c
	cat main.c >> test_custom.c

create_test11:
	echo 012345678901234567890123456789 > test11

# Clean up intermediate files and the executable
clean:
	rm -f $(TARGET) test*

# create test file refences real standard header file.
std: create_test11
	echo '#include "mirrordbg.h"' > test_std.c
	cat main.c >> test_std.c
	gcc -o test_std test_std.c

CC=gcc
CFLAGS=-Wall -ggdb

all: int_stack char_stack struct_stack

int_stack: int_stack_test.o
	$(CC) $(CFLAGS) $^ -o $@

char_stack: char_stack_test.o
	$(CC) $(CFLAGS) $^ -o $@

struct_stack: struct_stack_test.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	$(RM) -f int_stack *.o

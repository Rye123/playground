CC=gcc
CFLAGS=-Wall -ggdb

all: int_list_test

int_list_test: int_list_test.c int_list.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	$(RM) -f *.o int_list_test

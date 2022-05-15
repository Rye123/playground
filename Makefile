CC=gcc
CFLAGS=-Wall

main: main.c ArrayList/ArrayList.c
	$(CC) -o main main.c ArrayList/ArrayList.c
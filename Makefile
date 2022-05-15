CC=gcc
CFLAGS=-Wall

main: main.c ArrayList/ArrayList.c LinkedList/LinkedList.c
	$(CC) -o main main.c ArrayList/ArrayList.c LinkedList/LinkedList.c
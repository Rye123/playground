# MACROS
REMOVE = rm
CC = gcc

# RULES
all: prog_buffer prog_main executable
prog_buffer: ./buffer/buffer.c
	$(CC) -c ./buffer/buffer.c -o ./obj/buffer.o

prog_main: ./main.c
	$(CC) -c ./main.c -o ./obj/main.o

executable:
	$(CC) ./obj/* -o main


clean:
	$(REMOVE) ./obj/*

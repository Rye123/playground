# MACROS
REMOVE = rm
CC = g++
DEPENDENCIES = main.cpp string_helper.cpp framing.cpp
OUT = main

# RULES
all: prog

prog: $(DEPENDENCIES)
	$(CC) $(DEPENDENCIES) -o $(OUT)

clean:
	$(REMOVE) $(OUT)

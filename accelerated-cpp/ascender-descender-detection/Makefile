# REQUIRED MACROS
REMOVE = rm
CC = g++
DEPENDENCIES = main.cpp detect.cpp
OUT = main
TESTS = detect_test

# RULES
all: main

main: $(DEPENDENCIES)
	$(CC) $(DEPENDENCIES) -o $(OUT)

test: $(TESTS)

DETECT_TEST_DEPENDENCIES = detect_test.cpp detect.cpp
detect_test: $(DETECT_TEST_DEPENDENCIES)
	$(CC) $(DETECT_TEST_DEPENDENCIES) -o "detect_test"
	./detect_test
	rm "detect_test"

clean:
	rm main

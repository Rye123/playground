# REQUIRED MACROS
REMOVE = rm
CC = g++
DEPENDENCIES = main.cpp detect.cpp strmanip.cpp
OUT = main
TESTS = detect_test strmanip_test

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

STRMANIP_TEST_DEPENDENCIES = strmanip_test.cpp strmanip.cpp
strmanip_test: $(STRMANIP_TEST_DEPENDENCIES)
	$(CC) $(STRMANIP_TEST_DEPENDENCIES) -o "strmanip_test"
	./strmanip_test
	rm "strmanip_test"

clean:
	rm main

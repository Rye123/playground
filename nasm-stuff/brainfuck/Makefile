NAME=interpreter
SRC=$(NAME).asm
OBJ=$(NAME).o
OUT=$(NAME)

default:
	nasm -f elf $(SRC) -o $(OBJ)
	ld -m elf_i386 $(OBJ) -o $(OUT)

test:
	$(MAKE) default -s
	@echo "test out_a:"
	@cat test_files/out_a.bf | ./$(OUT)
	@echo "\ntest_out_a_jumps:"
	@cat test_files/out_a_jumps.bf | ./$(OUT)
	@echo "\ntest_out_b:"
	@cat test_files/out_b.bf | ./$(OUT)
	@echo "\ntest_out_abc:"
	@cat test_files/out_abc.bf | ./$(OUT)
	@echo "\ntest_hello_world:"
	@cat test_files/hello_world.bf | ./$(OUT)
	@echo "\n"

clean:
	$(RM) $(OBJ) $(OUT)

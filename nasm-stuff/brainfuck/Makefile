NAME=interpreter
SRC=$(NAME).asm
OBJ=$(NAME).o
OUT=$(NAME)

default:
	nasm -f elf $(SRC) -o $(OBJ)
	ld -m elf_i386 $(OBJ) -o $(OUT)

clean:
	$(RM) $(OBJ) $(OUT)

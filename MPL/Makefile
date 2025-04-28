FILENAME ?= practical01

all:
	nasm -f elf64 $(FILENAME).asm -o $(FILENAME).o
	ld $(FILENAME).o -o $(FILENAME)

run: all
	./$(FILENAME)

clean:
	rm -f $(FILENAME).o $(FILENAME)

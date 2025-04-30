# Default filename is 'practical01' if not provided
FILENAME ?= practical01

# Compilation rules
all:
	@echo "Assembling and Linking..."
	nasm -f elf64 $(FILENAME).asm -o $(FILENAME).o
	ld $(FILENAME).o -o $(FILENAME)

# Run the program after compiling
run: all
	@echo "Running the program..."
	./$(FILENAME)

# Clean up the compiled files
clean:
	@echo "Cleaning up..."
	rm -f $(FILENAME).o $(FILENAME)

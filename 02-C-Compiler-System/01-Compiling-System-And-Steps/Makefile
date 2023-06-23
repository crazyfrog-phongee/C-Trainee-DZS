TITLE_COLOR = \033[33m
NO_COLOR = \033[0m
FLAGS = -Wall -Werror
CC := gcc

.PHONY := stage1 stage2 stage3 stage4 clean-all

# Pre-processor
stage1:
	@echo "$(TITLE_COLOR)\n***** PREPROCESSOR *****$(NO_COLOR)"
	$(CC) -E hello_world.c -o hello_world.i

# Compiler
stage2:
	@echo "$(TITLE_COLOR)\n***** COMPILER *****$(NO_COLOR)"
	$(CC) -S hello_world.i -o hello_world.S

# Assembler
stage3:
	@echo "$(TITLE_COLOR)\n***** ASSEMBLER *****$(NO_COLOR)"
	$(CC) -c hello_world.S -o hello_world.o

# Linker
stage4:
	@echo "$(TITLE_COLOR)\n***** COMPILING *****$(NO_COLOR)"
	$(CC) -o hello_world hello_world.o

all:
	$(CC) -o hello_world hello_world.c $(FLAGS)

clean-all:
	rm -rf hello_world hello_world.i hello_world.S hello_world.o
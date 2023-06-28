TITLE_COLOR = \033[33m
NO_COLOR = \033[0m
FLAGS = -Wall -std=c99 -Werror -fdiagnostics-color=auto
CC := gcc

# when excuting make, compile all exe's
all: clean 
# When trying to compile one of the executables, first look for its .c files
# Then check if the libraries are in the lib folder
	@echo "$(TITLE_COLOR)\n***** CPPCHECK *****$(NO_COLOR)"
	cppcheck --enable=all --suppress=missingIncludeSystem stack.c
	@echo "$(TITLE_COLOR)\n***** COMPILING *****$(NO_COLOR)"
	$(CC) -S stack.c -o stack.o
	$(CC) -S stack_more_args.c -o stack_more_args.o
	$(CC) -o bin/stack_more_args -g $(FLAGS) stack_more_args.c
# do not look for files called clean, clean-all or this will be always a target
.PHONY: clean clean-all 

clean:
	rm -rf bin/*

leak: all
	@echo "$(TITLE_COLOR)\n***** LEAK CHECK *****$(NO_COLOR)"
	valgrind --leak-check=full -v --track-origins=yes --show-leak-kinds=all bin/test $(PORT)

run:
	@echo "$(TITLE_COLOR)\n***** RUNNING *****$(NO_COLOR)"
	./bin/test

debug:
	@echo "$(TITLE_COLOR)\n***** LEAK CHECK *****$(NO_COLOR)"
	gdb --tui bin/stack_more_args
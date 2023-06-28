TITLE_COLOR = \033[33m
NO_COLOR = \033[0m
FLAGS = -Wall -Werror
CC := gcc

# when excuting make, compile all exe's
all: clean-all 
	@echo "$(TITLE_COLOR)\n***** COMPILING *****$(NO_COLOR)"
	$(CC) -o bin/test nest_struct.c $(FLAGS)
	
# do not look for files called clean, clean-all or this will be always a target
.PHONY: clean-all 
clean-all:
	@echo "$(TITLE_COLOR)\n***** CLEANING *****$(NO_COLOR)"
	rm -rf bin/*

leak: all
	@echo "$(TITLE_COLOR)\n***** LEAK CHECK *****$(NO_COLOR)"
	valgrind --leak-check=full -v --track-origins=yes --show-leak-kinds=all bin/test
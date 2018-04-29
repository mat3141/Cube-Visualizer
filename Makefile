# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -g -O3
PROG = main
SRC = $(PROG).c cube.c
HDR = cube.h
OBJ = $(SRC:.c=.o)

# Targets
$(PROG): $(OBJ) -lm
$(OBJ): $(HDR)
TAGS: $(SRC) $(HDR)
	etags $^
.PHONY: clean
clean:
	$(RM) $(PROG) $(OBJ)

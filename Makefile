# build executable file 'chessprogram':
# 'make'

MAIN = chessprogram
CC = gcc
CFLAGS = -Isrc -Wall -Werror -Wextra -O3 -std=c99

SRC = main.c src/*.c
COMPILED = *.o src/*.o
RM = rm -r

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(SRC) -lm

clean:
	$(RM) $(MAIN) $(MAIN).dSYM $(COMPILED)

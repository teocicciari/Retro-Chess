# build executable file 'chessprogram':
# 'make'

MAIN = chessprogram
CC = gcc
CFLAGS = -I -Isrc -Wall -Werror -Wextra -O3 -std=c99

SRC = main.c src/*.c tests/*.c
COMPILED = *.o src/*.o tests/*.o
RM = rm -r

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(SRC) -lm

debug: $(OBJ)
	$(CC) -g $(CFLAGS) -o $(MAIN) $(SRC) -lm

clean:
	$(RM) $(MAIN)

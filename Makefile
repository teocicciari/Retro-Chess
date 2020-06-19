# build executable file 'chessprogram':
# 'make'

# removes all .o and executable files:
# 'make clean'

# COMPILER OPTS
CC = gcc
CFLAGS = -Isrc -Wall -Werror -Wextra -O3 -std=c99
RM = rm -rf

# SOURCES AND OBJECTS
SRC = main.c src/*.c
MAIN = chessprogram
COMPILED = *.o src/*.o

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(SRC) -lm

clean:
	$(RM) $(MAIN) $(MAIN).dSYM $(COMPILED)

#ifndef SQUARE_H
#define SQUARE_H

#include "../includes.h"

// Define structure
typedef struct _square_t *squares_t;

// Initialization
squares_t   new_square(squares_t moves, int r, int c);
squares_t   concat_moves(squares_t a, squares_t b);

// Get info
int get_column(squares_t square);
int get_row(squares_t square);

// AI utilities
squares_t get_random_move(squares_t moves);
int count_moves(squares_t move);

squares_t next_square(squares_t square);

#endif
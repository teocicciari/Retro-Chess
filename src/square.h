#ifndef SQUARE_H
#define SQUARE_H

#include "../includes.h"

typedef struct _square_t *  squares_t;

squares_t   add_move(int r, int c, squares_t moves);
squares_t   concat_moves(squares_t a, squares_t b);

// Get info

int get_column(squares_t square);
int get_row(squares_t square);
int get_moves_count(squares_t move);
squares_t next_square(squares_t square);

#endif
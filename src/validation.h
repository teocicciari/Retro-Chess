#ifndef validation_H
#define validation_H

#include "../includes.h"
#include "piece.h"
#include "board.h"

bool is_valid_square(int r, int c);
bool is_empty_square(int r, int c, pieces_t pieces);
bool is_capture(int r, int c, int color, pieces_t pieces);
bool valid_and_empty_or_capture(int r, int c, int color, pieces_t pieces);
void calculate_moves(pieces_t pieces, char color);
board_t move_(board_t board, char * move, int len);

#endif
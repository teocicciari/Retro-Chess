#ifndef VALIDATION_H
#define VALIDATION_H

#include "../includes.h"
#include "piece.h"
#include "square.h"
#include "board.h"

bool can_move(pieces_t piece);
bool is_valid_square(int row, int column);
bool is_empty_square(pieces_t pieces, int row, int column);
bool is_capture(pieces_t pieces, int row, int column, int color);
bool valid_and_empty_or_capture(pieces_t pieces, int row, int column, int color);
bool is_legal_move(pieces_t piece, char name, int row, int column);
bool is_posible_move(pieces_t pieces, char name, int row, int column);

void calculate_moves(board_t board, char color);
board_t move_(board_t board, char * move, int len);

#endif
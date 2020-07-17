#ifndef HELPERS_H
#define HELPERS_H

#include "../includes.h"
#include "piece.h"
#include "square.h"
#include "board.h"
#include "validation.h"

bool square_is_reachable(pieces_t pieces, bool color, int row, int column);
bool position_match(board_t board1, board_t board2);

int  column_to_int(char row);

bool piece_can_move(pieces_t piece);

bool is_pawn(char name);


bool is_in_check(board_t board, bool color);
bool is_checkmate(board_t board, bool color);
bool is_stalemate(board_t board, bool color);

bool is_valid_square(int row, int column);
bool is_empty_square(pieces_t pieces, int row, int column);
bool is_capture(pieces_t pieces, int row, int column, bool color);

bool valid_and_empty(pieces_t pieces, int row, int column);
bool valid_and_empty_or_capture(pieces_t pieces, int row, int column, int color);

bool is_legal_move(pieces_t piece, char name, int row, int column);
// Check if the move given is legal.

bool is_posible_move(pieces_t pieces, char name, int row, int column);
// Take all the pieces and check if some piece match the move.

#endif
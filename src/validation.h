#ifndef VALIDATION_H
#define VALIDATION_H

#include "../includes.h"
#include "piece.h"
#include "square.h"
#include "board.h"
#include "helpers.h"

void calculate_moves(board_t board, char color);
board_t move_(board_t board, char * move, int len);
bool is_valid_move(board_t board, char * move, int len);

#endif
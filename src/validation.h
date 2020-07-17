#ifndef VALIDATION_H
#define VALIDATION_H

#include "../includes.h"
#include "piece.h"
#include "square.h"
#include "board.h"
#include "helpers.h"

void    calculate_moves(board_t board, bool color);
bool    is_valid_move(board_t board, bool color, char * move, int len);
board_t process_move(board_t board, char * move, int len);

#endif
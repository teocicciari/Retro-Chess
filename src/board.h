#ifndef board_H
#define board_H

#include "../includes.h"
#include "piece.h"

typedef struct _board_t *board_t;

board_t empty_board();
board_t board_init(board_t board);
board_t destroy_board(board_t board);
board_t make_movement(board_t board, char name, char src_column, int src_row, char dest_columnest, int rowDest);
board_t add_piece_to_board(board_t board, char name, char color, int r, int c);

void print_board(board_t board);

pieces_t initial_position(pieces_t pieces);
pieces_t board_pieces(board_t board);

#endif
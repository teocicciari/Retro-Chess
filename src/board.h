#ifndef BOARD_H
#define BOARD_H

#include "../includes.h"
#include "piece.h"

typedef struct _board_t *board_t;

// Initialization
board_t     new_board();
board_t     board_init(board_t board);
board_t     copy_board(board_t board);

// Set & get info
pieces_t    get_board_pieces(board_t board);
board_t     set_board(board_t board, pieces_t pieces);

// Print
void        print_board(board_t board);

// Releasing
board_t     destroy_board(board_t board);


#endif
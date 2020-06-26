#ifndef board_H
#define board_H

typedef struct _board_t *board_t;

board_t empty_board();
board_t board_init(board_t board);
board_t destroy_board(board_t board);
board_t make_movement(board_t board, char name, char src_column, int src_row, char dest_columnest, int rowDest);

void print_board(board_t board);

pieces_t initial_position(pieces_t pieces);

#endif
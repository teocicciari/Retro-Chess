#ifndef PIECE_H
#define PIECE_H

#include "../includes.h"

// Define structures
typedef struct _piece_t *   pieces_t;
typedef struct _square_t *  squares_t;

pieces_t empty_pieces();
pieces_t add_piece(pieces_t pieces, char name, char color, int r, int c);
pieces_t destroy_pieces(pieces_t piece);
pieces_t move_piece(pieces_t pieces, char name, int src_c, int src_r, int dest_c, int dest_r);
pieces_t next_piece(pieces_t piece);
void     calculate_moves(pieces_t pieces, char turn);

// get info for piece
char  piece_name(pieces_t piece);
char piece_color(pieces_t piece);
int   piece_column(pieces_t piece);
int   piece_row(pieces_t piece);

squares_t add_move(int r, int c, squares_t moves);
void set_posible_moves(pieces_t piece, squares_t moves);

#endif

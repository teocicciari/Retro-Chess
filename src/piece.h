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
char    piece_name(pieces_t piece);
char    piece_color(pieces_t piece);
int     piece_column(pieces_t piece);
int     piece_row(pieces_t piece);

char    piece_name_cap(pieces_t piece);
int     column_to_int(char row);
bool    can_move(pieces_t piece);
int     get_pieces_count(pieces_t pieces);

// Posible moves
int         get_moves_count(pieces_t piece);
squares_t   get_posible_moves(pieces_t piece);
squares_t   add_move(int r, int c, squares_t moves);
squares_t   concat_moves(squares_t a, squares_t b);
void        set_posible_moves(pieces_t piece, squares_t moves);
void        print_posible_moves(pieces_t pieces);

int get_column(squares_t square);
int get_row(squares_t square);
squares_t next_square(squares_t square);

void set_position(pieces_t p, int c, int r);
pieces_t delete_piece(pieces_t pieces, pieces_t piece);
pieces_t search_piece(pieces_t pieces, int column, int row);

// Moves
pieces_t pawn_move(pieces_t pieces, int c, int r);
pieces_t pawn_capture(pieces_t pieces, int c_src, int c_dest, int r);
pieces_t simple_move(pieces_t pieces, char name, int c, int r);
pieces_t promotion(pieces_t pieces, int c, int r, char name);
pieces_t capture(pieces_t pieces, char name, int c, int r);
pieces_t from_row_move(pieces_t pieces, char name, int r_src, int c, int r_dest);
pieces_t from_column_move(pieces_t pieces, char name, int r_src, int c, int r_dest);
pieces_t capture_row_move(pieces_t pieces, char name, int r_src, int c, int r_dest);
pieces_t capture_column_move(pieces_t pieces, char name, int c_src, int c_dest, int r);

#endif

#ifndef PIECE_H
#define PIECE_H

#include "../includes.h"
#include "square.h"

// Define structures
typedef struct _piece_t     *pieces_t;
typedef struct _position_t  *position_t;

// Initialization
pieces_t    empty_pieces();
pieces_t    new_piece(pieces_t pieces, char name, char color, int row, int column);

// Set & get info
char        piece_name(pieces_t piece);
char        piece_name_cap(pieces_t piece);
void        set_name(pieces_t piece, char name);

char        piece_color(pieces_t piece);

void        set_position(pieces_t piece, int row, int column);
int         piece_column(pieces_t piece);
int         piece_row(pieces_t piece);

squares_t   get_posible_moves(pieces_t piece);
void        set_posible_moves(pieces_t piece, squares_t moves);

pieces_t    next_piece(pieces_t piece);
pieces_t    search_piece(pieces_t pieces, int row, int column);

// AI utilities
pieces_t    get_random_piece(pieces_t pieces);
int         count_pieces(pieces_t pieces);

// Releasing
pieces_t    delete_piece(pieces_t pieces, pieces_t piece);
pieces_t    destroy_pieces(pieces_t piece);

// move to another file
int         column_to_int(char row);

#endif

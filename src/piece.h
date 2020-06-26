#ifndef PIECE_H
#define PIECE_H

// Define structures
typedef struct _piece_t *pieces_t;
typedef struct _squares_t *squares_t;

pieces_t empty_pieces();
pieces_t new_piece(pieces_t pieces, int r, char c, char n);
pieces_t destroy_pieces(pieces_t piece);
pieces_t move_piece(pieces_t pieces, char name, char src_column, int src_row, char dest_column, int dest_row);
pieces_t next_piece(pieces_t piece);

// get info for piece
char piece_name(pieces_t piece);
char piece_column(pieces_t piece);
int  piece_row(pieces_t piece);


#endif

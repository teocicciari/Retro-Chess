#ifndef PIECE_H
#define PIECE_H

// Define structures
typedef struct _piece_t *pieces_t;
typedef struct _squares_t *squares_t;

pieces_t empty_pieces();
pieces_t new_piece(pieces_t pieces, int row, int column, char name);
pieces_t destroy_pieces(pieces_t piece);
pieces_t move_piece(pieces_t pieces, char name, int src_column, int src_row, int dest_column, int dest_row);
pieces_t next_piece(pieces_t piece);
void     calculate_moves(pieces_t pieces, char turn);

// get info for piece
char  piece_name(pieces_t piece);
int   piece_column(pieces_t piece);
int   piece_row(pieces_t piece);


#endif

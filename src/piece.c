#include "piece.h"
#include "validation.h"

struct _position_t {
	int row;
	int column;
};

struct _piece_t {
	char 		name;
	char 		color;
	position_t	position;
	squares_t 	posible_moves;
	pieces_t 	next;
};

// Initialization

pieces_t empty_pieces(){
	pieces_t pieces = NULL;
	return(pieces);
}

pieces_t add_piece(pieces_t pieces, char name, char color, int r, int c){
	pieces_t piece = calloc(1, sizeof(struct _piece_t));

	piece->name = name;
	piece->color = color;
	piece->position = calloc(1, sizeof(struct _position_t));
	piece->position->row = r;
	piece->position->column = c;
	piece->posible_moves = NULL;
	piece->next = pieces;

	return(piece);
}

// Set and get info of pieces

int get_pieces_count(pieces_t pieces){
	int count = 0;
	pieces_t p = pieces;
	do {
		count++;
		p = next_piece(p);
	} while (p != NULL);

	return count;
}

char piece_color(pieces_t piece){
	return(piece->color);
}

pieces_t next_piece(pieces_t piece){
	return(piece->next);
}

void set_position(pieces_t p, int c, int r){
	p->position->column = c;
	p->position->row = r;
}

void set_posible_moves(pieces_t piece, squares_t moves){
	piece->posible_moves = moves;
}

squares_t get_posible_moves(pieces_t piece){
	return piece->posible_moves;
}

// Name

char piece_name(pieces_t piece){
	return(piece->name);
}

char piece_name_cap(pieces_t piece){
	return(toupper(piece->name));
}

void set_name(pieces_t piece, char name){
	piece->name = name;
}

// Position

int piece_row(pieces_t piece){
	return(piece->position->row);
}

int piece_column(pieces_t piece){
	return(piece->position->column);
}

int column_to_int(char row){
	int result = 8;
    char rows[8] = {'a','b','c','d','e','f','g','h'};

	for (int i = 0; i < 8; i++) {
		if (row == rows[i]) { result = i;}
	}

	return result;
}

// Delete

pieces_t delete_piece(pieces_t pieces, pieces_t piece){
	pieces_t p = pieces;
	pieces_t result;

	if (p == piece) {
		result = next_piece(p);
		free(p);
		return result;
	}

	while ((next_piece(p) != NULL) && (next_piece(p) != piece)){
		p = next_piece(p);
	}

	if (next_piece(p) == NULL) {
		printf("DEBUG: piece not found");
		return pieces;
	}

	if (next_piece(p) == piece) {
		pieces_t delete = p->next;
		p->next = next_piece(p->next);
		free(delete);
	}

	return pieces;
}

pieces_t destroy_pieces(pieces_t piece){
	assert(piece != NULL);
	pieces_t p = piece->next;
	free(piece);
	while (p != NULL){
		p = p->next;
		free(p);
	}
	return(p);
}

pieces_t search_piece(pieces_t pieces, int column, int row) {
	pieces_t p = pieces;
	while (p != NULL){
		if ((piece_column(p) == column) && (piece_row(p) == row)){
			return p;
		}
		p = next_piece(p);
	}
	return NULL;
}

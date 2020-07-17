#include "piece.h"
#include "validation.h"

struct _position_t {
	int row;
	int column;
};

struct _piece_t {
	char 		name;
	bool 		color;
	position_t	position;
	squares_t 	posible_moves;
	pieces_t 	next;
};

pieces_t empty_pieces(){
	pieces_t pieces = NULL;
	return(pieces);
}

pieces_t new_piece(pieces_t pieces, char name, bool color, int r, int c){
	pieces_t piece = NULL;
	piece = calloc(1, sizeof(struct _piece_t));

	piece->name = name;
	piece->color = color;

	piece->position = calloc(1, sizeof(struct _position_t));
	piece->position->row = r;
	piece->position->column = c;

	piece->posible_moves = NULL;
	piece->next = pieces;

	return(piece);
}

pieces_t copy_pieces(pieces_t pieces){
	if (pieces == NULL) { return NULL; }

	pieces_t copy = empty_pieces();
	pieces_t piece = pieces;

	do{
		copy = new_piece(copy, piece->name, piece->color, 
				piece_row(piece), piece_column(piece));
		copy->posible_moves = copy_squares(piece->posible_moves);
	} while ((piece = piece->next) != NULL);
	
	return copy;
}

pieces_t set_initial_position(pieces_t pieces){
	// White's pieces
	pieces = new_piece(pieces, 'R', WHITE, 1, 0);
	pieces = new_piece(pieces, 'N', WHITE, 1, 1);
	pieces = new_piece(pieces, 'B', WHITE, 1, 2);
	pieces = new_piece(pieces, 'Q', WHITE, 1, 3);
	pieces = new_piece(pieces, 'K', WHITE, 1, 4);
	pieces = new_piece(pieces, 'B', WHITE, 1, 5);
	pieces = new_piece(pieces, 'N', WHITE, 1, 6);
	pieces = new_piece(pieces, 'R', WHITE, 1, 7);

	// Pawns
	for (int i=0;i<8;i++){
		pieces = new_piece(pieces, 'P', WHITE, 2, i);
	}

	// Black's pieces
	pieces = new_piece(pieces, 'r', BLACK, 8, 0);
	pieces = new_piece(pieces, 'n', BLACK, 8, 1);
	pieces = new_piece(pieces, 'b', BLACK, 8, 2);
	pieces = new_piece(pieces, 'q', BLACK, 8, 3);
	pieces = new_piece(pieces, 'k', BLACK, 8, 4);
	pieces = new_piece(pieces, 'b', BLACK, 8, 5);
	pieces = new_piece(pieces, 'n', BLACK, 8, 6);
	pieces = new_piece(pieces, 'r', BLACK, 8, 7);

	// Pawns
	for (int i=0;i<8;i++){
		pieces = new_piece(pieces, 'p', BLACK, 7, i);
	}

	return(pieces);
}

bool piece_color(pieces_t piece){
	assert(piece != NULL);
	return(piece->color);
}

void set_position(pieces_t piece, int row, int column){
	assert(piece != NULL);

	piece->position->row = row;
	piece->position->column = column;
}

squares_t get_posible_moves(pieces_t piece){
	assert(piece != NULL);
	
	return piece->posible_moves;
}

void set_posible_moves(pieces_t piece, squares_t moves){
	assert(piece != NULL);
	
	piece->posible_moves = moves;
}

char piece_name(pieces_t piece){
	assert(piece != NULL);
	
	return(piece->name);
}

char piece_name_capitalized(pieces_t piece){
	assert(piece != NULL);
	
	return(toupper(piece->name));
}

void set_name(pieces_t piece, char name){
	assert(piece != NULL);
	
	piece->name = name;
}

int piece_row(pieces_t piece){
	assert(piece != NULL);
	
	return(piece->position->row);
}

int piece_column(pieces_t piece){
	assert(piece != NULL);
	
	return(piece->position->column);
}

char piece_column_char(pieces_t piece){
	char columns[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	return columns[piece->position->column];
}

pieces_t search_piece(pieces_t pieces, int row, int column) {
	assert(pieces != NULL);
	
	pieces_t p = pieces;
	while (p != NULL){
		if ((piece_column(p) == column) && (piece_row(p) == row)){
			return p;
		}
		p = next_piece(p);
	}
	return NULL;
}

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

int count_pieces(pieces_t pieces){
	int count = 0;
	pieces_t p = pieces;
	do {
		count++;
		p = next_piece(p);
	} while (p != NULL);

	return count;
}

pieces_t get_random_piece(pieces_t pieces){
    pieces_t piece = pieces;
    time_t t;

    int len = count_pieces(pieces);
    srand((unsigned) time(&t));

    int index = rand() % len;
    while (index != 0){
        index--;
        piece = next_piece(piece);
    }

    return piece;
}

pieces_t next_piece(pieces_t piece){
	return(piece->next);
}

void destroy_pieces(pieces_t pieces){
	assert(pieces != NULL);

	pieces_t piece = pieces->next;
	pieces_t next = NULL;

	do {
		next = piece->next;
		if (piece->posible_moves != NULL){
			destroy_squares(piece->posible_moves);
		}
		free(piece);
		piece = next;
	} while (piece != NULL);
}
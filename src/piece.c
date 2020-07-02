#include "piece.h"

struct _piece_t {
	char 				name;
	char 				color;
	squares_t		position;
	squares_t 	posible_moves;
	pieces_t 		next;
};

struct _square_t {
	int 				row;		// 1 - 8
	int 				column;	// 0='a'- 7='h'
	squares_t 	nextSq;
};

pieces_t empty_pieces(){
	pieces_t pieces = NULL;
	return(pieces);
}

pieces_t add_piece(pieces_t pieces, char name, char color, int r, int c){
	pieces_t piece = calloc(1, sizeof(struct _piece_t));

	piece->name = name;
	piece->color = color;
	piece->position = calloc(1, sizeof(struct _square_t));
	piece->position->row = r;
	piece->position->column = c;
	piece->position->nextSq = NULL;
	piece->posible_moves = NULL;
	piece->next = pieces;

	return(piece);
}

char piece_name(pieces_t piece){
	return(piece->name);
}

char piece_color(pieces_t piece){
	return(piece->color);
}

int piece_column(pieces_t piece){
	return(piece->position->column);
}

int piece_row(pieces_t piece){
	return(piece->position->row);
}

pieces_t next_piece(pieces_t piece){
	return(piece->next);
}

squares_t add_move(int r, int c, squares_t moves){
	squares_t move = NULL;
	move = calloc(1, sizeof(struct _square_t));

	move->row = r;
	move->column = c;
	move->nextSq = NULL;

	if (moves != NULL) {
		move->nextSq = moves;
	}

	return move;
}

void set_posible_moves(pieces_t piece, squares_t moves){
	piece->posible_moves = moves;
}


bool is_posible_move(pieces_t pieces, char name, int r, int c){
	squares_t moves;

	do {
		if (piece_name(pieces) == name) {
			moves = pieces->posible_moves;
			do {
				if (moves->column == c && moves->row == r){
					return true;
				}
			} while ((moves = moves->nextSq) != NULL);
		}
	} while ((pieces = next_piece(pieces)) != NULL);

	return false;
}

pieces_t delete_piece(pieces_t pieces, pieces_t piece){
	pieces_t p = pieces;
	pieces_t result;

	if (pieces == piece) {
		result = next_piece(pieces);
		free(pieces);
		return result;
	}

	while (next_piece(p) != piece && next_piece(p) != NULL){
		p = next_piece(p);
	}

	if (next_piece(p) == piece) {
		result = next_piece(p->next);
		free(p->next);
		p->next = NULL;

		p = result;

		while (next_piece(p) != NULL){
			p = next_piece(p);
		}
		p->next = pieces;
	} else {
		printf("DEBUG: Piece not found");
		return pieces;
	}

	return result;
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

/* Moving a piece, old code.. eventually deleted */


pieces_t search_piece(pieces_t pieces, char name, int col, int row) {
	pieces_t piece = NULL;
	if ((piece_row(pieces) != row) | (piece_column(pieces) != col)) {
		while((next_piece(pieces) != NULL) & !((piece_row(pieces) == row) & (piece_column(pieces) == col))) {
			pieces = next_piece(pieces);
		}
	}
	if ((piece_row(pieces) == row) & (piece_column(pieces) == col) & (piece_name(pieces) == name)) {
		piece = pieces;
	}
	return(piece);
}

pieces_t move_piece(pieces_t pieces, char name, int src_column, int src_row, int dest_column, int dest_row){
	pieces_t piece = search_piece(pieces, name, src_column, src_row);
	pieces_t p = pieces;

	if (piece == NULL){
		printf("\nPiece not found\n");
	}
	else if (pieces != piece){
		while (next_piece(pieces) != piece){
			pieces = next_piece(pieces);
		}
		pieces->next = piece->next;
		piece->position->column = dest_column;
		piece->position->row = dest_row;
		piece->next = p;
		pieces = piece;
	}
	else if (pieces == piece){
		piece->position->column = dest_column;
		piece->position->row = dest_row;
	}
	else {
		printf("\nDEBUG: something wrong\n");
	}
	return(pieces);
}

void print_posible_moves(pieces_t pieces) {
  char columns[8] = {'a','b','c','d','e','f','g','h'};
	pieces_t p = pieces;
	squares_t moves;
	char c;
	int r;

	do {
		moves = p->posible_moves;
		assert(moves != NULL);
		printf("%c: ", piece_name(p));
		
		do {
			r = moves->row;
			c = columns[moves->column];
			printf("%c%d ", c, r);
		} while ((moves = moves->nextSq) != NULL);
		printf("\n");
		
	} while ((p = next_piece(p)) != NULL);
	
}
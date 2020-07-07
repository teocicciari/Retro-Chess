#include "piece.h"

struct _piece_t {
	char 		name;
	char 		color;
	squares_t	position;
	squares_t 	posible_moves;
	pieces_t 	next;
};

struct _square_t {
	int 		row;		// 1 - 8
	int 		column;		// 0='a'- 7='h'
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

char piece_name_cap(pieces_t piece){
	return(toupper(piece->name));
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

squares_t concat_moves(squares_t a, squares_t b){
	squares_t result = a;
	if (a == NULL) {
		return b;
	}

	while(a->nextSq != NULL) {
		a = a->nextSq;
	}
	a->nextSq = b;

	return result;
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


/* for DEBUG */

void print_posible_moves(pieces_t pieces) {
  char columns[8] = {'a','b','c','d','e','f','g','h'};
	pieces_t p = pieces;
	squares_t moves;
	char c;
	int r;

	do {
		moves = p->posible_moves;
		printf("%c: ", piece_name(p));

		if (moves == NULL) {
			printf("can't move :(");
		} else {
			do {
				r = moves->row;
				c = columns[moves->column];
				printf("%c%d ", c, r);
			} while ((moves = moves->nextSq) != NULL);
		}
		
		printf("\n");
		
	} while ((p = next_piece(p)) != NULL);
	
}

// Moves & captures

bool is_pos_move(pieces_t piece, char name, int c, int r){
	if(piece->name != name){ return false; }
	if (piece->posible_moves == NULL){ return false; }

	squares_t moves = piece->posible_moves;
	while(moves->nextSq != NULL){
		if ((moves->column == c) && (moves->row == r)){
			return true;
		}
		moves = moves->nextSq;
	} if ((moves->column == c) && (moves->row == r)){
		return true;
	}

	return false;
}

void set_position(pieces_t p, int c, int r){
	p->position->column = c;
	p->position->row = r;
}

pieces_t pawn_move(pieces_t pieces, int c, int r){
	pieces_t p = pieces;
	char name = 'P';

	while (p != NULL){
		if (is_pos_move(p, name, c, r)){
			set_position(p, c, r);
		}
		p = p->next;
	}

	return pieces;
}


pieces_t pawn_capture(pieces_t pieces, int c_src, int c_dest, int r){
	if (c_src && c_dest && r){
		return NULL;
	}
	return pieces;
}
pieces_t simple_move(pieces_t pieces, char name, int c, int r){
	if (c && r && name){
		return NULL;
	}
	return pieces;
}
pieces_t promotion(pieces_t pieces, int c, int r){
	if (c && r){
		return NULL;
	}
	return pieces;
}
pieces_t capture(pieces_t pieces, char name, int c, int r){
	if (c && name && r){
		return NULL;
	}
	return pieces;
}

pieces_t from_row_move(pieces_t pieces, char name, int r_src, int c, int r_dest){
	if (c && r_dest && r_src && name){
		return NULL;
	}
	return pieces;
}


pieces_t from_column_move(pieces_t pieces, char name, int r_src, int c, int r_dest){
	if (r_src && r_dest && c && name){
		return NULL;
	}
	return pieces;

}
pieces_t capture_column_move(pieces_t pieces, char name, int c_src, int c_dest, int r){
	if (c_src && c_dest && r && name){
		return NULL;
	}
	return pieces;

}

pieces_t capture_row_move(pieces_t pieces, char name, int r_src, int c, int r_dest){
	if (r_src && r_dest && c && name){
		return NULL;
	}
	return pieces;

}
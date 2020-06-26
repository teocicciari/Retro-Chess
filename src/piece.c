#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piece.h"

struct _piece_t {
	int 				row;
	char 				column;
	char 				name;
	squares_t 	mov_pos;
	pieces_t 		next;
};

struct _squares_t {
	int 				row;
	char 				column;
	squares_t 	nextSq;
};

pieces_t empty_pieces(){
	pieces_t pieces = NULL;
	return(pieces);
}

pieces_t new_piece(pieces_t pieces, int r, char c, char n){
	pieces_t piece = calloc(1, sizeof(struct _piece_t));
	piece->row = r;
	piece->column = c;
	piece->name = n;
	piece->next = pieces;
	return(piece);
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

pieces_t search_piece(pieces_t pieces, char name, char col, int row) {
	pieces_t piece = NULL;
	if ((pieces->row != row) | (pieces->column != col)) {
		while((pieces->next != NULL) & !((pieces->row == row) & (pieces->column == col))) {
			pieces = pieces->next;
		}
	}
	if ((pieces->row == row) & (pieces->column == col) & (pieces->name == name)) {
		piece = pieces;
	}
	return(piece);
}

pieces_t move_piece(pieces_t pieces, char name, char src_column, int src_row, char dest_column, int dest_row){
	pieces_t piece = search_piece(pieces, name, src_column, src_row);
	pieces_t p = pieces;
	if (piece == NULL){
		printf("\nIncorrect move\n");
	}
	else if (pieces != piece){
		while (pieces->next != piece){
			pieces = pieces->next;
		}
		pieces->next = piece->next;
		piece->column = dest_column;
		piece->row = dest_row;
		piece->next = p;
		pieces = piece;
	}
	else if (pieces == piece){
		piece->column = dest_column;
		piece->row = dest_row;
	}
	else {
		printf("\nSomething wrong\n");
	}
	return(pieces);
}

char piece_name(pieces_t piece){
	return(piece->name);
}

char piece_column(pieces_t piece){
	return(piece->column);
}

int piece_row(pieces_t piece){
	return(piece->row);
}

pieces_t next_piece(pieces_t piece){
	return(piece->next);
}

/*

pieces_t delete_piece(pieces_t pieces, pieces_t piece){
	pieces_t piece = NULL;
}

bool validate_move(pieces_t board, jugada mov){
}

*/
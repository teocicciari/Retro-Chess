#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piece.h"

struct _piece_t {
	int 				row;
	int 				column;
	char 				name;
	squares_t 	mov_pos;
	pieces_t 		next;
};

struct _squares_t {
	int 				row;
	int 				column;
	squares_t 	nextSq;
};

pieces_t empty_pieces(){
	pieces_t pieces = NULL;
	return(pieces);
}

pieces_t new_piece(pieces_t pieces, int row, int column, char name){
	pieces_t piece = calloc(1, sizeof(struct _piece_t));
	piece->row = row;
	piece->column = column;
	piece->name = name;
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

pieces_t search_piece(pieces_t pieces, char name, int col, int row) {
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

pieces_t move_piece(pieces_t pieces, char name, int src_column, int src_row, int dest_column, int dest_row){
	pieces_t piece = search_piece(pieces, name, src_column, src_row);
	pieces_t p = pieces;

	calculate_moves(p, 'b');

	if (piece == NULL){
		printf("\nPiece not found\n");
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

int piece_column(pieces_t piece){
	return(piece->column);
}

int piece_row(pieces_t piece){
	return(piece->row);
}

pieces_t next_piece(pieces_t piece){
	return(piece->next);
}

void calculate_moves(pieces_t pieces, char turn) {
	int board[8][8];
	pieces_t p = pieces;
	
	if (turn == 'a') {
		turn = 'b';
	} else {
		turn = 'c';
	} 

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = 0;
		}
	}

	while (p != NULL) {
		switch (p->name) 
		{
		case 'r':
			board[p->column][p->row - 1] = -4;
			break;
		case 'n':
			board[p->column][p->row - 1] = -2;
			break;
		case 'b':
			board[p->column][p->row - 1] = -3;
			break;
		case 'q':
			board[p->column][p->row - 1] = -9;
			break;
		case 'k':
			board[p->column][p->row - 1] = -10;
			break;
		case 'p':
			board[p->column][p->row - 1] = -1;
			break;
		case 'R':
			board[p->column][p->row - 1] = 4;
			break;
		case 'N':
			board[p->column][p->row - 1] = 2;
			break;
		case 'B':
			board[p->column][p->row - 1] = 3;
			break;
		case 'Q':
			board[p->column][p->row - 1] = 9;
			break;
		case 'K':
			board[p->column][p->row - 1] = 10;
			break;
		case 'P':
			board[p->column][p->row - 1] = 1;
			break;
		default:
			break;
		}
		p = p->next;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d\t", board[j][i]);
		}
		printf("\n");
	}
	
}

/*

pieces_t delete_piece(pieces_t pieces, pieces_t piece){
	pieces_t piece = NULL;
}

bool validate_move(pieces_t board, jugada mov){
}

*/
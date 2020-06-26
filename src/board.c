#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piece.h"
#include "board.h"

struct _board_t{
	pieces_t 			pieces;
	unsigned int 	length;
};

board_t empty_board(){
	board_t board;
	board = calloc(1, sizeof(struct _board_t));
	board->pieces = empty_pieces();
	board->length = 0;
	return(board);
}

board_t board_init(board_t board){
	board->length = 32;
	board->pieces = initial_position(board->pieces);
	return(board);
}

board_t destroy_board(board_t board){
	assert(board != NULL);
	board->pieces = destroy_pieces(board->pieces);
	free(board);
	board = NULL;
	return(board);
}

board_t make_movement(board_t board, char piece, char src_column, int src_row, char dest_column, int dest_row){
	board->pieces = move_piece(board->pieces, piece, src_column, src_row, dest_column, dest_row);
	return(board);
}

pieces_t initial_position(pieces_t pieces){
	char col[8] = {'a','b','c','d','e','f','g','h'};

	pieces = new_piece(pieces, 1, 'a', 'T');
	pieces = new_piece(pieces, 1, 'b', 'C');
	pieces = new_piece(pieces, 1, 'c', 'A');
	pieces = new_piece(pieces, 1, 'd', 'D');
	pieces = new_piece(pieces, 1, 'e', 'R');
	pieces = new_piece(pieces, 1, 'f', 'A');
	pieces = new_piece(pieces, 1, 'g', 'C');
	pieces = new_piece(pieces, 1, 'h', 'T');

	pieces = new_piece(pieces, 8, 'a', 't');
	pieces = new_piece(pieces, 8, 'b', 'c');
	pieces = new_piece(pieces, 8, 'c', 'a');
	pieces = new_piece(pieces, 8, 'd', 'd');
	pieces = new_piece(pieces, 8, 'e', 'r');
	pieces = new_piece(pieces, 8, 'f', 'a');
	pieces = new_piece(pieces, 8, 'g', 'c');
	pieces = new_piece(pieces, 8, 'h', 't');

	for (int i=0;i<8;i++){
		pieces = new_piece(pieces, 7, col[i], 'p');
	}
	for (int i=0;i<8;i++){
		pieces = new_piece(pieces, 2, col[i], 'P');
	}
	return(pieces);
}

void print_board(board_t board){
	int rowN = 8;
	pieces_t pieces = NULL;
	pieces = board->pieces;

	char col[8] = {'a','b','c','d','e','f','g','h'};
	char tab[8][8];

	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){ 
			tab[i][j] = ' ';
		}
	}

	while (pieces != NULL){
		int i = 0;
		while ((piece_column(pieces) != col[i]) & (i<8)){ 
			i++;
		}
		int j = 1;
		while ((piece_row(pieces) != j) & (j<9)){ 
			j++;
		}
		j--;
		tab[j][i] = piece_name(pieces);
		pieces = next_piece(pieces);
	}

	printf("\t   ___________________________________\n");
	printf("\t---|                                 |\n");
	for (int i=8;i>0;i--){
		printf("\t %d | ", rowN);
		rowN--;
		for (int j=0;j<8;j++){ 
			printf("[%c] ", tab[i-1][j]);
		}
		if (i == 1){
			printf("|\n\t---|_________________________________|\n");
		}else{
			printf ("|\n\t---|                                 |\n");
		}
	}
	printf("\t    | a | b | c | d | e | f | g | h |\n\n");
	printf("     q: exit to menu // b: one move back // r: restart game\n\n");
}
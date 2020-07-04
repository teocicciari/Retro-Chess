#include "board.h"

struct _board_t {
	pieces_t 		pieces;
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

board_t add_piece_to_board(board_t board, char name, char color, int r, int c) {
	board->pieces = add_piece(board->pieces, name, color, r, c);
	return board;
}

pieces_t board_pieces(board_t board){
	return board->pieces;
}

pieces_t initial_position(pieces_t pieces){
	pieces = add_piece(pieces, 'R', 'w', 1, 0);
	pieces = add_piece(pieces, 'N', 'w', 1, 1);
	pieces = add_piece(pieces, 'B', 'w', 1, 2);
	pieces = add_piece(pieces, 'Q', 'w', 1, 3);
	pieces = add_piece(pieces, 'K', 'w', 1, 4);
	pieces = add_piece(pieces, 'B', 'w', 1, 5);
	pieces = add_piece(pieces, 'N', 'w', 1, 6);
	pieces = add_piece(pieces, 'R', 'w', 1, 7);

	pieces = add_piece(pieces, 'r', 'b', 8, 0);
	pieces = add_piece(pieces, 'n', 'b', 8, 1);
	pieces = add_piece(pieces, 'b', 'b', 8, 2);
	pieces = add_piece(pieces, 'q', 'b', 8, 3);
	pieces = add_piece(pieces, 'k', 'b', 8, 4);
	pieces = add_piece(pieces, 'b', 'b', 8, 5);
	pieces = add_piece(pieces, 'n', 'b', 8, 6);
	pieces = add_piece(pieces, 'r', 'b', 8, 7);

	for (int i=0;i<8;i++){
		pieces = add_piece(pieces, 'p', 'b', 7, i);
	}
	for (int i=0;i<8;i++){
		pieces = add_piece(pieces, 'P', 'w', 2, i);
	}
	return(pieces);
}

void print_board(board_t board){
	int rowN = 8;
	pieces_t pieces = NULL;
	pieces = board->pieces;

	char tab[8][8];

	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){ 
			tab[i][j] = ' ';
		}
	}

	while (pieces != NULL){
		int i = 0;
		while ((piece_column(pieces) != i) & (i<8)){ 
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
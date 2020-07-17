#include "board.h"
#include "piece.h"

struct _board_t {
	pieces_t 	pieces;
	bool		game_finished;
};

board_t new_board(){
	board_t board;
	board = calloc(1, sizeof(struct _board_t));

	board->pieces = empty_pieces();
	board->game_finished = 0;

	return(board);
}

board_t board_init(board_t board){
	board->pieces = set_initial_position(board->pieces);

	return(board);
} 

board_t copy_board(board_t board){
	board_t copy;
	copy = calloc(1, sizeof(struct _board_t));

	copy->pieces = copy_pieces(board->pieces);

	copy->game_finished = board->game_finished;

	return(copy);
}

pieces_t get_board_pieces(board_t board){
	return board->pieces;
}

board_t set_board(board_t board, pieces_t pieces){
	board->pieces = pieces;
	return board;
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
	printf("\t   q: exit to menu - r: restart game\n\n");
}

board_t destroy_board(board_t board){
	assert(board != NULL);

	if (board->pieces != NULL){
		destroy_pieces(board->pieces);
	}

	free(board);

	board = NULL;
	return(board);
}

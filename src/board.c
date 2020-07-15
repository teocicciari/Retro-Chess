#include "board.h"
#include "piece.h"

struct _board_t {
	pieces_t 	pieces;

	char *		last_move;
	bool		w_long_castle;
	bool		w_short_castle;
	bool		b_long_castle;
	bool		b_short_castle;
	bool		game_finished;
};

board_t empty_board(){
	board_t board;

	board = calloc(1, sizeof(struct _board_t));
	board->pieces = empty_pieces();

	board->last_move = NULL;
	board->w_long_castle = 0;
	board->w_short_castle = 0;
	board->b_long_castle = 0;
	board->b_short_castle = 0;
	board->game_finished = 0;

	return(board);
}

board_t board_init(board_t board){
	board->pieces = set_initial_position(board->pieces);
	board->w_long_castle = 1;
	board->w_short_castle = 1;
	board->b_long_castle = 1;
	board->b_short_castle = 1;

	return(board);
}

board_t destroy_board(board_t board){
	assert(board != NULL);
	board->pieces = destroy_pieces(board->pieces);
	free(board);
	board = NULL;
	return(board);
}

pieces_t get_board_pieces(board_t board){
	return board->pieces;
}

board_t set_board(board_t board, pieces_t pieces){
	board->pieces = pieces;
	return board;
}

pieces_t set_initial_position(pieces_t pieces){
	pieces = new_piece(pieces, 'R', 'w', 1, 0);
	pieces = new_piece(pieces, 'N', 'w', 1, 1);
	pieces = new_piece(pieces, 'B', 'w', 1, 2);
	pieces = new_piece(pieces, 'Q', 'w', 1, 3);
	pieces = new_piece(pieces, 'K', 'w', 1, 4);
	pieces = new_piece(pieces, 'B', 'w', 1, 5);
	pieces = new_piece(pieces, 'N', 'w', 1, 6);
	pieces = new_piece(pieces, 'R', 'w', 1, 7);

	pieces = new_piece(pieces, 'r', 'b', 8, 0);
	pieces = new_piece(pieces, 'n', 'b', 8, 1);
	pieces = new_piece(pieces, 'b', 'b', 8, 2);
	pieces = new_piece(pieces, 'q', 'b', 8, 3);
	pieces = new_piece(pieces, 'k', 'b', 8, 4);
	pieces = new_piece(pieces, 'b', 'b', 8, 5);
	pieces = new_piece(pieces, 'n', 'b', 8, 6);
	pieces = new_piece(pieces, 'r', 'b', 8, 7);

	for (int i=0;i<8;i++){
		pieces = new_piece(pieces, 'p', 'b', 7, i);
	}
	for (int i=0;i<8;i++){
		pieces = new_piece(pieces, 'P', 'w', 2, i);
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
	printf("\t   q: exit to menu - r: restart game\n\n");
}
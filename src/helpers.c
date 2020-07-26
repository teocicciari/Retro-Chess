#include "helpers.h"

char get_input(void) {
    char input = '\0';
    char line[10];

    if (fgets(line, sizeof line, stdin) != NULL) {
        input = line[0];
    }

    return(input);
}

char * get_move(void) {
    char * line;
    line = calloc(256, sizeof(char));

    if (fgets(line, 256*sizeof(char), stdin) == NULL) {
        printf("move fail");
        return(NULL);
    }

    return line;
}

int column_to_int(char column){
    char columns[8] = {'a','b','c','d','e','f','g','h'};

	for (int i = 0; i < 8; i++) {
		if (column == columns[i]) { return i;}
	}

	return -1;
}

char column_to_char(int column){
	char columns[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	return columns[column];
}

bool piece_can_move(pieces_t piece){
	if (get_posible_moves(piece) != NULL){
		return true;
	}
	return false;
}

bool player_can_move(pieces_t pieces){
	pieces_t piece = pieces;
	do {
		if (piece_can_move(piece)) {
			return true;
		}
	} while ((piece = next_piece(piece)) != NULL);

	return false;
}

pieces_t get_king(pieces_t pieces, bool color){
	pieces_t piece = pieces;

	do {
		if (piece_color(piece) == color && piece_name_capitalized(piece) == 'K'){
			return piece;
		}
	} while ((piece = next_piece(piece)) != NULL);
	
	return NULL;
}

bool is_pawn(char name){
	char pos[5] = {'Q','N','B','R','K'};
	for (int i = 0; i<5; i++){
		if (pos[i] == name){
			return false;
		}
	}
	return true;
}

bool is_in_check(board_t board, bool color){
	bool result = false;
	board_t copy = copy_board(board);

	pieces_t pieces = get_board_pieces(copy);
	pieces_t king = get_king(pieces, color);

	if (king == NULL){
		printf("King not found :o"); 
		return false; 
	}

	int row = piece_row(king);
	int column = piece_column(king);

	calculate_moves(copy, !color);

	if (square_is_reachable(pieces, !color, row, column)){
		printf("Your king is not safe!\n");
		result = true;
	}

	destroy_board(copy);
	return result;
}

bool is_checkmate(board_t board, bool color){
	pieces_t pieces = get_board_pieces(board);
	if (!player_can_move(pieces) && is_in_check(board, color)){
		return true;
	}
	return false;
}

bool is_stalemate(board_t board, bool color){
	pieces_t pieces = get_board_pieces(board);
	if (!player_can_move(pieces) && !(is_in_check(board, color))){
		return true;
	}
	return false;
}

bool is_valid_square(int r, int c) {
	if (r < 1 || r > 8 || c < 0 || c > 7) {
		return false;
	} else {
		return true;
	}
}

bool is_empty_square(pieces_t pieces, int r, int c) {
	while (pieces != NULL){
		if(piece_row(pieces) == r && piece_column(pieces) == c){
			return false;
		}
		pieces = next_piece(pieces);
	}
	return true;
}

bool is_capture(pieces_t pieces, int r, int c, bool color) {
	while (pieces != NULL){
		if (piece_row(pieces) == r && piece_column(pieces) == c){
			if (piece_color(pieces) != color) 
				return true;
		}
		pieces = next_piece(pieces);
	}
	return false;
}

bool valid_and_empty(pieces_t pieces, int r, int c){
	if (is_valid_square(r, c) && (is_empty_square(pieces, r, c))) {
		return true;
	} else {
		return false;
	}
}

bool valid_and_empty_or_capture(pieces_t pieces, int r, int c, int color){
	if (is_valid_square(r, c) && 
		 (is_empty_square(pieces, r, c) || 
			is_capture(pieces, r, c, color))) {
		return true;
	} else {
		return false;
	}
}

bool square_is_reachable(pieces_t pieces, bool color, int row, int column){
	squares_t moves;
	pieces_t p = pieces;

	do {
		moves = get_posible_moves(p);
		if (moves == NULL) { continue; }
		do {
			if (piece_color(p) == color && square_match(moves, row, column)){
				if ((piece_name_capitalized(p) == 'P') &&
					(piece_column(p) == column)){
						continue;
				}
				return true;
			}
		} while ((moves = next_square(moves)) != NULL);
	} while ((p = next_piece(p)) != NULL);

	return false;
}

bool is_posible_move(pieces_t pieces, char name, int row, int column){
	/*
	Take all the pieces and check if some piece match the move
	*/
	squares_t moves;

	do {
		if (piece_name(pieces) == name) {
			moves = get_posible_moves(pieces);
			do {
				if (square_match(moves, row, column)){
					return true;
				}
			} while ((moves = next_square(moves)) != NULL);
		}
	} while ((pieces = next_piece(pieces)) != NULL);

	return false;
}

bool is_legal_move(pieces_t piece, char name, int r, int c){
	/*
	Check if the piece given is legal 
	*/
	if (piece_name(piece) != name){ return false; }
	if (get_posible_moves(piece) == NULL){ return false; }

	squares_t moves = get_posible_moves(piece);
	while(next_square(moves) != NULL){
		if ((get_column(moves) == c) && (get_row(moves) == r)){
			return true;
		}
		moves = next_square(moves);
	} if ((get_column(moves) == c) && (get_row(moves) == r)){
		return true;
	}

	return false;
}

bool position_match(board_t board1, board_t board2){
	assert(board2 != NULL && board1 != NULL);

	pieces_t board1_pieces = get_board_pieces(board1);
	pieces_t board2_pieces = get_board_pieces(board2);

	pieces_t p1 = NULL, p2 = NULL;

	p1 = board1_pieces;
	do
	{
		p2 = search_piece(board2_pieces, piece_row(p1), piece_column(p1));
		if (p2 == NULL || piece_name(p1) != piece_name(p2)){
			return false;
		}

	} while ((p1 = next_piece(p1)) != NULL);
	

	return true; 
}
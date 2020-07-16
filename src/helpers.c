#include "helpers.h"

int column_to_int(char row){
	int result = 8;
    char rows[8] = {'a','b','c','d','e','f','g','h'};

	for (int i = 0; i < 8; i++) {
		if (row == rows[i]) { result = i;}
	}

	return result;
}

bool can_move(pieces_t piece){
	if (get_posible_moves(piece) != NULL){
		return true;
	}
	return false;
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

bool is_capture(pieces_t pieces, int r, int c, int color) {
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

bool is_posible_move(pieces_t pieces, char name, int r, int c){
	/*
	Take all the pieces and check if some piece match the move
	*/
	squares_t moves;

	do {
		if (piece_name(pieces) == name) {
			moves = get_posible_moves(pieces);
			do {
				if (get_column(moves) == c && get_row(moves) == r){
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
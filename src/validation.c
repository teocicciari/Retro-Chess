#include "validation.h"

bool is_valid_square(int r, int c) {
	if (r < 1 || r > 8 || c < 0 || c > 7) {
		return false;
	} else {
		return true;
	}
}

bool is_empty_square(int r, int c, pieces_t pieces) {
	while (pieces != NULL){
		if(piece_row(pieces) == r && piece_column(pieces) == c){
			return false;
		}
		pieces = next_piece(pieces);
	}
	return true;
}

bool is_capture(int r, int c, int color, pieces_t pieces) {
	while (pieces != NULL){
		if (piece_row(pieces) == r && piece_column(pieces) == c){
			if (piece_color(pieces) != color) 
				return true;
		}
		pieces = next_piece(pieces);
	}
	return false;
}

bool valid_and_empty(int r, int c, pieces_t pieces){
	if (is_valid_square(r, c) && (is_empty_square(r, c, pieces))) {
		return true;
	} else {
		return false;
	}
}

bool valid_and_empty_or_capture(int r, int c, int color, pieces_t pieces){
	if (is_valid_square(r, c) && 
		 (is_empty_square(r, c, pieces) || 
			is_capture(r, c, color, pieces))) {
		return true;
	} else {
		return false;
	}
}

squares_t pawn_moves(pieces_t pawn, pieces_t pieces){
	squares_t result = NULL;

	int r = piece_row(pawn);
	int c = piece_column(pawn);
	int color = piece_color(pawn);

	int start = 2; int step = 1;
	if (color == 'b'){
		start = 7; step = -1;
	}

	if (valid_and_empty(r + step, c, pieces)) {
		result = add_move(r + step, c, result);
		if (r == start) {
			if (valid_and_empty(r + (2*step), c, pieces)) {
				result = add_move(r + (2*step), c, result);
			}
		}
	}
	

	if (is_capture(r + step, c + 1, color, pieces)) {
		result = add_move(r + step, c + 1, result);
	}
	if (is_capture(r + step, c - 1, color, pieces)) {
		result = add_move(r + step, c - 1, result);
	}

	return result;
}

squares_t knight_moves(pieces_t knight, pieces_t pieces){
	squares_t result = NULL;

	int r = piece_row(knight);
	int c = piece_column(knight);
	int color = piece_color(knight);

	int rows[8] = 		{r+2, r+2, r+1, r+1, r-1, r-1, r-2, r-2};
	int columns[8] = 	{c+1, c-1, c+2, c-2, c+2, c-2, c+1, c-1};

	for (int i = 0; i<8; i++) {
		if (valid_and_empty_or_capture(rows[i], columns[i], color, pieces)) { 
			result = add_move(rows[i], columns[i], result); 
		}
	}

	return result;
}

squares_t bishop_moves(pieces_t bishop, pieces_t pieces){
	squares_t result = NULL;
	int r, c;

	int row = piece_row(bishop);
	int column = piece_column(bishop);
	int color = piece_color(bishop);

	int rows[4] = 		{1, 1, -1, -1};
	int columns[4] = 	{1, -1, 1, -1};

	for (int i = 0; i < 4; i++) {
		r = row; c = column;
		while (valid_and_empty(r + rows[i], c + columns[i], pieces)) {
			result = add_move(r + rows[i], c + columns[i], result);
			r = r + rows[i]; 
			c = c + columns[i];
		}
		if (is_capture(r + rows[i], c + columns[i], color, pieces)){
			result = add_move(r + rows[i], c + columns[i], result);
		}
	}

	return result;
}

squares_t rook_moves(pieces_t rook, pieces_t pieces){
	squares_t result = NULL;
	int r, c;

	int row = piece_row(rook);
	int column = piece_column(rook);
	int color = piece_color(rook);

	int rows[4] = 		{1, -1, 0, 0};
	int columns[4] = 	{0, 0, 1, -1};

	for (int i = 0; i < 4; i++) {
		r = row; c = column;
		while (valid_and_empty(r + rows[i], c + columns[i], pieces)) {
			result = add_move(r + rows[i], c + columns[i], result);
			r = r + rows[i]; 
			c = c + columns[i];
		}
		if (is_capture(r + rows[i], c + columns[i], color, pieces)){
			result = add_move(r + rows[i], c + columns[i], result);
		}
	}

	return result;
}

squares_t queen_moves(pieces_t queen, pieces_t pieces){
	return concat_moves(bishop_moves(queen, pieces), rook_moves(queen, pieces));
}

squares_t king_moves(pieces_t king, pieces_t pieces){
	squares_t result = NULL;

	int r = piece_row(king);
	int c = piece_column(king);
	int color = piece_color(king);

	int rows[8] = 		{r+1, r+1, r+1, r	 , r	, r-1, r-1, r-1};
	int columns[8] = 	{c	, c-1, c+1, c-1, c+1, c	 , c+1, c-1};

	for (int i = 0; i<8; i++) {
		if (valid_and_empty_or_capture(rows[i], columns[i], color, pieces)){ 
			result = add_move(rows[i], columns[i], result); 
		}
	}

	return result;
}

void calculate_moves(pieces_t pieces, char color) {
	pieces_t p = pieces;
	squares_t moves;

	do {
		if (p != NULL && piece_color(p) == color) {
			moves = NULL;

			switch (piece_name_cap(p))
			{
			case 'P':
				moves = pawn_moves(p, pieces);
				break;
			case 'R':
				moves = rook_moves(p, pieces);
				break;
			case 'N':
				moves = knight_moves(p, pieces);
				break;
			case 'B':
				moves = bishop_moves(p, pieces);
				break;
			case 'K':
				moves = king_moves(p, pieces);
				break;
			case 'Q':
				moves = queen_moves(p, pieces);
				break;
			default:
				printf("\ncase fail\n");
				break;
			}

			set_posible_moves(p, moves);
		} 
	} while ((p = next_piece(p)) != NULL);
}

int column_to_int(char row){
	int result = 8;
    char rows[8] = {'a','b','c','d','e','f','g','h'};

	for (int i = 0; i < 8; i++) {
		if (row == rows[i]) { result = i;}
	}
	return result;
}

board_t move_(board_t board, char * move, int len){
    char name = move[0];
    int c_src, c_dest, r_src, r_dest;
	pieces_t pieces = board_pieces(board);

	switch (len)
	{
	case 2:
		c_dest = column_to_int(move[0]);
		r_dest = move[1] - '0';
		board = set_board(board, pawn_move(pieces, c_dest, r_dest));
		break;
	case 3:
		if (move[1] == 'x'){
			c_src = column_to_int(move[0]);
			c_dest = column_to_int(move[2]);
			r_dest = move[3] - '0';
			board = set_board(board, pawn_capture(pieces, c_src, c_dest, r_dest));
		} else {
			c_dest = column_to_int(move[1]);
			r_dest = move[2] - '0';;
			board = set_board(board, simple_move(pieces, name, c_dest, r_dest));
		}
		break;
	case 4:
		if (move[2] == '='){
			c_dest = column_to_int(move[0]);
			r_dest = move[1] - '0';
			board = set_board(board, promotion(pieces, c_dest, r_dest));
		} else if (move[1] == 'x'){
			c_dest = column_to_int(move[2]);
			r_dest = move[3] - '0';
			board = set_board(board, capture(pieces, name, c_dest, r_dest));
		} else if (column_to_int(move[1]) == 8) { // It's not a column
			r_src = move[1] - '0';
			c_dest = column_to_int(move[2]);
			r_dest = move[3] - '0';
			board = set_board(board, from_row_move(pieces, name, r_src, c_dest, r_dest));
		} else {
			c_src = column_to_int(move[1]);
			c_dest = column_to_int(move[2]);
			r_dest = move[3] - '0';
			board = set_board(board, from_column_move(pieces, name, c_src, c_dest, r_dest));
		}
		break;
	case 5:
		if (column_to_int(move[1]) == 8) {
			r_src = move[1] - '0';
			c_dest = column_to_int(move[3]);
			r_dest = move[4] - '0';
			board = set_board(board, capture_row_move(pieces, name, r_src, c_dest, r_dest));
		} else {
			c_src = column_to_int(move[1]);
			c_dest = column_to_int(move[3]);
			r_dest = move[4] - '0';
			board = set_board(board, capture_column_move(pieces, name, c_src, c_dest, r_dest));
		}
		break;
	}

    free(move);
    return(board);
} 

/*
bool is_in_check(int r, int c, int color, pieces_t pieces){
	// TODO: Check if the king can move to that square without being devored
	// 1 - calculate enemy moves
	// 2 - check if (r, c) is in the posible_moves of the enemy
	// situation: recursive loop if there is only one square between kings
	return false;
}
*/
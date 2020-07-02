#include "../includes.h"
#include "piece.h"

bool is_valid_square(int r, int c) {
	if (r < 0 || r > 7 || c < 0 || c > 7) {
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

bool valid_and_empty_or_capture(int r, int c, int color, pieces_t pieces){
	/*
	 Returns true if the square (r,c) is inside of the board, 
	 doesn't have a piece inside or 
	 if it does have a piece inside it's an enemy's piece 
	*/
	if (is_valid_square(r, c) && 
		 (is_empty_square(r, c, pieces) || 
			is_capture(r, c, color, pieces))) {
		return true;
	} else {
		return false;
	}
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

void calculate_moves(pieces_t pieces, char color) {
	pieces_t p = pieces;
	squares_t moves;

	while (next_piece(p) != NULL) {
		if (piece_color(p) == color) {
			moves = NULL;

			switch (piece_name(p))
			{
      /*
			case 'P':
				moves = pawn_moves(p, pieces);
				break;
			case 'R':
				moves = rook_moves(p, pieces);
				break;
      */
			case 'N':
				moves = knight_moves(p, pieces);
				break;
      /*
			case 'B':
				moves = bishop_moves(p, pieces);
				break;
			case 'K':
				moves = king_moves(p, pieces);
				break;
			case 'Q':
				moves = queen_moves(p, pieces);
				break;
			*/
			default:
				printf("\nDEBUG: case fail\n");
				break;
			}

			if (moves != NULL) { 
				set_posible_moves(p, moves); 
			} else {
				printf("\nDEBUG: moves is NULL\n");
			}
		}

		p = next_piece(p);
	}
}

/*
bool is_in_check(int r, int c, int color, pieces_t pieces){
	// TODO: Check if the king can move to that square without being devored
	// 1 - calculate enemy moves
	// 2 - check if (r, c) is in the posible_moves of the enemy
	// situation: recursive loop if there is only one square between kings
	return false;
}

squares_t king_moves(pieces_t king, pieces_t pieces){
	squares_t result = NULL;

	int r = king->position->row;
	int c = king->position->column;
	int color = king->color;

	int rows[8] = 		{r+1, r+1, r+1, r	 , r	, r-1, r-1, r-1};
	int columns[8] = 	{c	, c-1, c+1, c-1, c+1, c	 , c+1, c-1};

	for (int i = 0; i<8; i++) {
		if (valid_and_empty_or_enemy(rows[i], columns[i], color, pieces) &&
				!is_in_check(r, c, color, pieces)){ 
			result = addMove(rows[i], columns[i], result); 
		}
	}

	return result;
}
*/
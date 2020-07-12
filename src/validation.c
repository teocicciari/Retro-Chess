#include "validation.h"

bool can_move(pieces_t piece){
	if (get_posible_moves(piece) != NULL){
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

bool is_posible_move(pieces_t pieces, char name, int r, int c){
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

bool is_pos_move(pieces_t piece, char name, int c, int r){
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

// Moves

pieces_t pawn_move(pieces_t pieces, int c, int r){
	pieces_t p = pieces;
	char name = 'P';

	while (p != NULL){
		if (is_pos_move(p, name, c, r)){
			set_position(p, c, r);
		}
		p = next_piece(p);
	}

	return pieces;
}

pieces_t simple_move(pieces_t pieces, char name, int c, int r){
	pieces_t p = pieces;

	while (p != NULL){
		if (piece_name(p) == name && is_pos_move(p, name, c, r) &&
					is_empty_square(r, c, pieces)){
			set_position(p, c, r);
		}
		p = next_piece(p);
	}

	return pieces;
}

pieces_t promotion(pieces_t pieces, int c, int r, char new_name){
	pieces_t p = pieces;
	char name = 'P';

	while (p != NULL){
		if (is_pos_move(p, name, c, r)){
			set_position(p, c, r);
			set_name(p, new_name);
		}
		p = next_piece(p);
	}

	return pieces;
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

pieces_t capture(pieces_t pieces, char name, int c, int r){
	// could be a pawn capture!
	pieces_t delete;
	pieces_t p = pieces;

	if (is_pawn(name)){
		while (p != NULL){
			if (is_pos_move(p, 'P', c, r) && 
					piece_column(p) == column_to_int(name)){
				delete = search_piece(pieces, c, r);
				pieces = delete_piece(pieces, delete);
				set_position(p, c, r);
			}
		p = next_piece(p);
		}
	}
	else {
		while (p != NULL){
			if (is_pos_move(p, name, c, r)){
				delete = search_piece(pieces, c, r);
				pieces = delete_piece(pieces, delete);
				set_position(p, c, r);
			}
		p = next_piece(p);
		}
	}

	return pieces;
}

pieces_t from_row_move(pieces_t pieces, char name, int r_src, int c, int r_dest){
	pieces_t p = pieces;

	while (p != NULL){
		if (piece_name(p) == name && is_pos_move(p, name, c, r_dest) &&
					r_src == piece_row(p) &&
					is_empty_square(r_dest, c, pieces)){
			set_position(p, c, r_dest);
		}
		p = next_piece(p);
	}

	return pieces;
}

pieces_t from_column_move(pieces_t pieces, char name, int c_src, int c_dest, int r_dest){
	pieces_t p = pieces;

	while (p != NULL){
		if (piece_name(p) == name && is_pos_move(p, name, c_dest, r_dest) &&
					c_src == piece_column(p) &&
					is_empty_square(r_dest, c_dest, pieces)){
			set_position(p, c_dest, r_dest);
		}
		p = next_piece(p);
	}

	return pieces;
}

pieces_t capture_column_move(pieces_t pieces, char name, int c_src, int c_dest, int r){
	pieces_t p = pieces;
	pieces_t delete;

	while (p != NULL){
		if (piece_name(p) == name && is_pos_move(p, name, c_dest, r) &&
					c_src == piece_column(p) &&
					is_empty_square(r, c_dest, pieces)){

			delete = search_piece(pieces, c_dest, r);
			pieces = delete_piece(pieces, delete);
			set_position(p, c_dest, r);
		}
		p = next_piece(p);
	}

	return pieces;
}

pieces_t capture_row_move(pieces_t pieces, char name, int r_src, int c, int r_dest){
	pieces_t p = pieces;
	pieces_t delete;

	while (p != NULL){
		if (piece_name(p) == name && is_pos_move(p, name, c, r_dest) &&
					r_src == piece_row(p) &&
					is_empty_square(r_dest, c, pieces)){

			delete = search_piece(pieces, c, r_dest);
			pieces = delete_piece(pieces, delete);
			set_position(p, c, r_dest);
		}
		p = next_piece(p);
	}

	return pieces;
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
		c_dest = column_to_int(move[1]);
		r_dest = move[2] - '0';
		board = set_board(board, simple_move(pieces, name, c_dest, r_dest));
		break;

	case 4:
		if (move[2] == '='){
			c_dest = column_to_int(move[0]);
			r_dest = move[1] - '0';
			char new_name = move[3];
			board = set_board(board, promotion(pieces, c_dest, r_dest, new_name));
		} 
		else if (move[1] == 'x'){
			c_dest = column_to_int(move[2]);
			r_dest = move[3] - '0';
			board = set_board(board, capture(pieces, name, c_dest, r_dest));
		} 
		else if (column_to_int(move[1]) == 8) { // It's not a column
			r_src = move[1] - '0';
			c_dest = column_to_int(move[2]);
			r_dest = move[3] - '0';
			board = set_board(board, from_row_move(pieces, name, r_src, c_dest, r_dest));
		} 
		else {
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
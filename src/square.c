#include "square.h"
#include "piece.h"

struct _square_t {
	int 		row;		// 1 - 8
	int 		column;		// 0='a'- 7='h'
	squares_t 	next;
};

squares_t new_square(squares_t squares, int r, int c){
	squares_t move = NULL;
	move = calloc(1, sizeof(struct _square_t));

	move->row = r;
	move->column = c;
	move->next = NULL;

	if (squares != NULL) {
		move->next = squares;
	}

	return move;
}

squares_t copy_squares(squares_t squares){
	if (squares == NULL){
		return NULL;
	}

	squares_t copy = NULL;
	squares_t square = squares;

	do{
		copy = new_square(copy, square->row, square->column);
	} while ((square = square->next) != NULL);
	
	return copy;
}

squares_t concat_moves(squares_t a, squares_t b){
	squares_t result = a;
	if (a == NULL) {
		return b;
	}

	while(a->next != NULL) {
		a = a->next;
	}
	a->next = b;

	return result;
}

int get_column(squares_t square){
	return square->column;
}


int get_row(squares_t square){
	return square->row;
}

char get_row_char(squares_t square){
	char rows[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
	return rows[square->row];
}

bool square_match(squares_t square, int row, int column){
	if ((square->column == column) && (square->row == row)){
		return true;
	}
	return false;
}

int count_moves(squares_t move){
	int count = 0;
	if (move == NULL) { return count; }

	do{
		count++;
		move = move->next;
	} while (move != NULL);

	return count;
}

squares_t get_random_move(squares_t moves){
    time_t t;
    
    int len = count_moves(moves);
    srand((unsigned) time(&t));

    int index = rand() % len;
    while (index > 0){
        index--;
        moves = next_square(moves);
    }

    return moves;
}

squares_t next_square(squares_t square){
	return square->next;
}

void destroy_squares(squares_t squares){
	assert(squares != NULL);

	squares_t square = squares;
	squares_t next = NULL;

	do {
		next = square->next;
		free(square);
		square = next;
	} while (square != NULL);
}
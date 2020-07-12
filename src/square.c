#include "square.h"
#include "piece.h"

struct _square_t {
	int 		row;		// 1 - 8
	int 		column;		// 0='a'- 7='h'
	squares_t 	nextSq;
};

squares_t add_move(int r, int c, squares_t moves){
	squares_t move = NULL;
	move = calloc(1, sizeof(struct _square_t));

	move->row = r;
	move->column = c;
	move->nextSq = NULL;

	if (moves != NULL) {
		move->nextSq = moves;
	}

	return move;
}

squares_t concat_moves(squares_t a, squares_t b){
	squares_t result = a;
	if (a == NULL) {
		return b;
	}

	while(a->nextSq != NULL) {
		a = a->nextSq;
	}
	a->nextSq = b;

	return result;
}

// Get info

int get_column(squares_t square){
	return square->column;
}

int get_row(squares_t square){
	return square->row;
}

int get_moves_count(squares_t move){
	int count = 0;
	if (move == NULL) { return count; }

	do{
		count++;
		move = move->nextSq;
	} while (move != NULL);

	return count;
}

squares_t next_square(squares_t square){
	return square->nextSq;
}
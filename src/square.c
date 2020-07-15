#include "square.h"
#include "piece.h"

struct _square_t {
	int 		row;		// 1 - 8
	int 		column;		// 0='a'- 7='h'
	squares_t 	nextSq;
};

squares_t new_square(squares_t squares, int r, int c){
	squares_t move = NULL;
	move = calloc(1, sizeof(struct _square_t));

	move->row = r;
	move->column = c;
	move->nextSq = NULL;

	if (squares != NULL) {
		move->nextSq = squares;
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

int get_column(squares_t square){
	return square->column;
}

int get_row(squares_t square){
	return square->row;
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

int count_moves(squares_t move){
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
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/piece.h"
#include "src/board.h"
#include "src/print.h"

#define START     's'
#define RESTART   'r'
#define OPTIONS   'o'
#define BACK      'b'
#define QUIT      'q'

char get_input(void) {
    char input = '\0';
    char line[10];

    if (fgets(line, sizeof line, stdin) != NULL) {
        input = line[0];
    }

    return(input);
}

char * get_move() {
    char * line;
    line = calloc(10, sizeof(char));

    if (fgets(line, sizeof line, stdin) == NULL) {
        printf("move fail");
        return(NULL);
    }

    return line;
}

board_t move_(board_t board, char * m){
    int src_column = m[2] - '0';
    int dest_column = m[4] - '0';

    board = make_movement(board, m[0], m[1], src_column, m[3], dest_column);
    free(m);
    return(board);
}

int main(void) {
    char input = 'n';
    char * move;

    board_t board = empty_board();
    board = board_init(board);

    print_init();
    input = get_input();
    
    switch (input)
    {
    case START:
        start_message();
        break;
    case OPTIONS:
        print_options();
        break;
    case QUIT:
        quit_message();
        return(EXIT_SUCCESS);
    default:
        return(EXIT_SUCCESS);
    }
    
    print_board(board);
    first_move_message();

    do {
        move = get_move();
        switch (move[0]) {
	        case RESTART:
                board = destroy_board(board);
                board = empty_board();
                board = board_init(board);
                print_board(board);
	            break;
	        case QUIT:
	            quit_message2();
	            return (EXIT_SUCCESS);
	        default:
	            board = move_(board, move);
                print_board(board);
	            break;
        }
    } while (1); // !gameFinished

    return(EXIT_SUCCESS);
}
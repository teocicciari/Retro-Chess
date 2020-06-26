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

board_t move(board_t board){
    char line[5];
    int src_column, dest_column;

    if (fgets(line, sizeof line, stdin) == NULL) {
        printf("move fail");
        return(NULL);
    }
    
    src_column = line[2] - '0';
    dest_column = line[4] - '0';

    board = make_movement(board, line[0], line[1], src_column, line[3], dest_column);
    return(board);
}

int main(void) {
    char input = 'n';

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
    
    do {
        first_move_message();
        input = get_input();
        switch (input) {
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
	            board = move(board);
                print_board(board);
	            break;
        }
    } while (input != QUIT);

    return(EXIT_SUCCESS);
}
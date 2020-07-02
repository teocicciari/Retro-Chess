#include "includes.h"

#include "src/piece.h"
#include "src/board.h"
#include "src/print.h"
#include "tests/test.h"

#define START     's'
#define TEST      't'
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


board_t move_(board_t board, char * move){
    int src_row, dest_row;
    char rows[8] = {'a','b','c','d','e','f','g','h'};
    
    for (int i = 0; i < 8; i++) {
        if(move[1] == rows[i]){
            src_row = i;
        } if(move[3] == rows[i]){
            dest_row = i;
        }
    }

    char name = move[0];
    int src_column = move[2] - '0';
    int dest_column = move[4] - '0';

    board = make_movement(board, name, src_row, src_column, dest_row, dest_column);
    free(move);
    return(board);
} 

int main(void) {
    char input = 'n';
    char * move;

    board_t board = empty_board();
    
    print_init();
    input = get_input();
    
    switch (input)
    {
    case START:
        start_message();
        board = board_init(board);
        break;
    case OPTIONS:
        print_options();
        break;
    case TEST:
        tests(board);
        return(EXIT_SUCCESS);
    case QUIT:
    default:
        quit_message();
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
                board = destroy_board(board);
	            quit_message2();
	            return (EXIT_SUCCESS);
	        default:
	            board = move_(board, move);
                print_board(board);
	            break;
        }

        move_message();
    } while (1); // !gameFinished

    return(EXIT_SUCCESS);
}
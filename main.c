#include "includes.h"

#include "src/piece.h"
#include "src/board.h"
#include "src/print.h"
#include "src/AI.h"

#include "tests/test.h"

#define START     's'
#define TEST      't'
#define RESTART   'r'
#define OPTIONS   'o'
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

int main(void) {
    char input = 'n';
    char * move;

    board_t b;
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
        board = board_init(board);
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
        int len = strlen(move) - 1;
        calculate_moves(board, 'w');

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
                while ((b = move_(board, move, len)) == NULL){
                    move = get_move();
                    len = strlen(move) - 1;
                }
                board = b;

                calculate_moves(board, 'w');
                print_board(board);

                thinking();
                
                board = AI_response(board, 'b');
                print_board(board);
	            break;
        }

        move_message();
    } while (1); // !gameFinished

    return(EXIT_SUCCESS);
}
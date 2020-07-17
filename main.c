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
    line = calloc(256, sizeof(char));

    if (fgets(line, 256*sizeof(char), stdin) == NULL) {
        printf("move fail");
        return(NULL);
    }

    return line;
}

int main(void) {
    char input = 'n';
    char * move;

    board_t board = new_board();
    
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
        calculate_moves(board, WHITE);

        switch (move[0]) {
	        case RESTART:   
                board = destroy_board(board);
                board = new_board();
                board = board_init(board);
                print_board(board);
	            break;

	        case QUIT:
                board = destroy_board(board);
	            quit_message2();
	            return (EXIT_SUCCESS);
                
	        default:
                if (!(is_valid_move(board, WHITE, move, len))) {
                    printf("Imposible move, try again!\n");
                } else {
                    board = process_move(board, move, len);
                    calculate_moves(board, WHITE);
                    print_board(board);

                    thinking();
                    
                    board = AI_response(board, BLACK);
                    calculate_moves(board, BLACK);
                    print_board(board);
                }

	            break;
        }

        move_message();
    } while (1); // !gameFinished

    return(EXIT_SUCCESS);
}
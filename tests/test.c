#include "test.h"

#define NEW_PIECE       'n'
#define MOVE            'm'
#define PRINT_PIECES    'p'
#define QUIT            'q'

char * get_piece() {
    char * line;
    line = calloc(10, sizeof(char));

    if (fgets(line, sizeof line, stdin) == NULL) {
        printf("move fail");
        return(NULL);
    }

    return line;
}

char * get_move2() {
    char * line;
    line = calloc(10, sizeof(char));
    printf("\n>> ");

    if (fgets(line, sizeof line, stdin) == NULL) {
        printf("move fail");
        return(NULL);
    }

    return line;
}

char get_input2(void) {
    char input = '\0';
    char line[10];

    if (fgets(line, sizeof line, stdin) != NULL) {
        input = line[0];
    }

    return(input);
}

board_t put_piece(board_t board){
  printf("\nAdd piece: ");
  char * piece = get_piece();

  char color = piece[0];
  char name = piece[1];

  int row = piece[3] - '0';
  int column;

  char columns[8] = {'a','b','c','d','e','f','g','h'};
  
  for (int i = 0; i < 8; i++) {
      if(piece[2] == columns[i]){
          column = i;
      }
  }

  pieces_t pieces = get_board_pieces(board);
  pieces = new_piece(pieces, name, color, row, column);
  board = set_board(board, pieces);
  free(piece);
  return(board);
} 

void tests(board_t board) {
  print_tests();
  char input;
  char * move;
  bool quit = false;
  pieces_t pieces = get_board_pieces(board);
  
  do
  {
    printf("> ");
    input = get_input2();
    switch (input)
    {
    case MOVE:
      move = get_move2();
      int len = strlen(move) - 1;
      board = move_(board, move, len);
      pieces = get_board_pieces(board);
      calculate_moves(pieces, 'w');
      break;
    case NEW_PIECE:
      board = put_piece(board);
      pieces = get_board_pieces(board);
      calculate_moves(pieces, 'w');
      calculate_moves(pieces, 'b');
      break;
    case PRINT_PIECES:
      pieces = get_board_pieces(board);
      print_board(board);
      break;
    case QUIT:
      quit = true;
      break;
    }
  } while (!quit);
}
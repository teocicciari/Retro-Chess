#include "test.h"

char * get_piece() {
    char * line;
    line = calloc(10, sizeof(char));

    if (fgets(line, sizeof line, stdin) == NULL) {
        printf("move fail");
        return(NULL);
    }

    return line;
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

  board = add_piece_to_board(board, name, color, row, column);
  free(piece);
  return(board);
} 

void tests(board_t board) {

  board = put_piece(board);

  print_board(board);
}
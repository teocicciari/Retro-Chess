#include "piece.h"
#include "validation.h"
#include "AI.h"

#include <time.h>

pieces_t get_random_piece(pieces_t pieces){
    pieces_t p = pieces;
    time_t t;
    int len = get_pieces_count(pieces);
    srand((unsigned) time(&t));
    int index = rand() % len;

    while (index != 0){
        index--;
        p = next_piece(p);
    }

    return p;
}

squares_t get_random_move(pieces_t piece){
    time_t t;
    squares_t square = get_posible_moves(piece);
    int len = get_moves_count(piece);
    srand((unsigned) time(&t));
    int index = rand() % len;

    while (index > 0){
        index--;
        square = next_square(square);
    }

    return square;
}

board_t AI_response(board_t board, char color){
	pieces_t pieces = board_pieces(board);
    pieces_t piece, delete;
    squares_t move;

    calculate_moves(pieces, color);
    
    do {
        piece = get_random_piece(pieces);
    } while ((piece_color(piece) != color) || (!can_move(piece)));
    
    move = get_random_move(piece);
    char column = get_column(move);
    char row = get_row(move);
    
    if (!(is_empty_square(row, column, pieces))){
        delete = search_piece(pieces, column, row);
        pieces = delete_piece(pieces, delete);
    }
    set_position(piece, column, row);

    board = set_board(board, pieces);
    return board;
}
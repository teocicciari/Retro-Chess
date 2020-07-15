#include "piece.h"
#include "square.h"
#include "validation.h"
#include "AI.h"

board_t AI_response(board_t board, char color){
	pieces_t pieces = get_board_pieces(board);
    pieces_t piece, delete;
    squares_t moves, move;

    calculate_moves(pieces, color);
    
    // Choose a random piece
    do {
        piece = get_random_piece(pieces);
    } while ((piece_color(piece) != color) || (!can_move(piece)));
    
    // Choose a random move!
    moves = get_posible_moves(piece);
    move = get_random_move(moves);
    
    char column = get_column(move);
    char row = get_row(move);
    
    // Make the move!!
    if (!(is_empty_square(pieces, row, column))){
        delete = search_piece(pieces, row, column);
        pieces = delete_piece(pieces, delete);
    }
    set_position(piece, row, column);
    board = set_board(board, pieces);

    return board;
}
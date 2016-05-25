#pragma once

/*
Class for the chessboard of the game
*/

#define CHESSBOARD_ROW 13
#define CHESSBOARD_COLUMN 26
#define GRID_NUMBER 9

class ChessBoard {
public:
    ChessBoard();

    // Place a human chess piece at the chessboard
    // pos is from 0 to 8
    void placeHuman(const int pos);

    // Place a computer chess piece at the chessboard
    // pos is from 0 to 8
    void placeComp(const int pos);

    // Unplace a chess piece at the chessboard
    // pos is from 0 to 8
    void unPlace(const int pos);

    // Print the board to console
    void print();

    // Judge whether the chessboard is full
    bool isFull() const;

    // Judge whether the postion on the chessboard is empty
    bool isEmpty(const int post) const;

    // Judge if the computer can win after placing
    // chess piece at a position, if so, store the position
    // in @param bestMove
    bool compCanWinImmediately(int &bestMove);

    // Judge if the human can win after placing
    // chess piece at a position, if so, store the position
    // in @param bestMove
    bool humanCanWinImmediately(int &bestMove);

    // Judge if the computer wins the game
    bool compWin() const;

    // Judge if the huamn wins the game
    bool humanWin() const;

private:

    // Judge if the chess piece type in the board can win the game
    bool hasWon(const char c) const;

    // The board one-dimension used for calculation
    char boardInOneDimens[GRID_NUMBER];

    // The board two-dimension array to be printed to console
    char board[CHESSBOARD_ROW][CHESSBOARD_COLUMN] = {
        "- - - - - - - - - - - - -",
        "|       |       |       |",
        "|       |       |       |",
        "|       |       |       |",
        "- - - - - - - - - - - - -",
        "|       |       |       |",
        "|       |       |       |",
        "|       |       |       |",
        "- - - - - - - - - - - - -",
        "|       |       |       |",
        "|       |       |       |",
        "|       |       |       |",
        "- - - - - - - - - - - - -"
    };
};

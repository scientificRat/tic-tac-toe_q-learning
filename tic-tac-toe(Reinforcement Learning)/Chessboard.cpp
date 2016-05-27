#include "Chessboard.h"

#define HUMAN_CHAR 'O'
#define COMP_CHAR 'X'
#define BLANK_CHAR ' '

ChessBoard::ChessBoard() {
    for (int i = 0; i < GRID_NUMBER; ++i) {
        boardInOneDimens[i] = BLANK_CHAR;
    }
}

void ChessBoard::placeHuman(const int pos) {
    if (pos >= 0 && pos <= 8) {
        boardInOneDimens[pos] = HUMAN_CHAR;
    }
}

void ChessBoard::placeComp(const int pos) {
    if (pos >= 0 && pos <= 8) {
        boardInOneDimens[pos] = COMP_CHAR;
    }
}

void ChessBoard::unPlace(const int pos) {
    if (pos >= 0 && pos <= 8) {
        boardInOneDimens[pos] = BLANK_CHAR;
    }
}

bool ChessBoard::isFull() const {
    for (int i = 0; i < GRID_NUMBER; ++i) {
        if (boardInOneDimens[i] == BLANK_CHAR) {
            return false;
        }
    }
    return true;
}

bool ChessBoard::isEmpty(const int pos) const {
    return boardInOneDimens[pos] == BLANK_CHAR;
}

bool ChessBoard::compCanWinImmediately(int &bestMove) {
    for (int i = 0; i < GRID_NUMBER; ++i) {
        if (isEmpty(i)) {
            boardInOneDimens[i] = COMP_CHAR;
            bool canWin = compWin();
            boardInOneDimens[i] = BLANK_CHAR;
            if (canWin) {
                bestMove = i;
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::humanCanWinImmediately(int &bestMove) {
    for (int i = 0; i < GRID_NUMBER; ++i) {
        if (isEmpty(i)) {
            boardInOneDimens[i] = HUMAN_CHAR;
            bool canWin = humanWin();
            boardInOneDimens[i] = BLANK_CHAR;
            if (canWin) {
                bestMove = i;
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::compWin() const {
    return hasWon(COMP_CHAR);
}

bool ChessBoard::humanWin() const {
    return hasWon(HUMAN_CHAR);
}

bool ChessBoard::hasWon(const char c) const {
    // Check rows
    for (int i = 0; i <= 6; i += 3)
        if (boardInOneDimens[i] == c && boardInOneDimens[i] == boardInOneDimens[i + 1]
            && boardInOneDimens[i] == boardInOneDimens[i + 2]) return true;

    // Check columns
    for (int i = 0; i <= 3; ++i)
        if (boardInOneDimens[i] == c && boardInOneDimens[i] == boardInOneDimens[i + 3]
            && boardInOneDimens[i] == boardInOneDimens[i + 6]) return true;

    // Check diagonals
    if (boardInOneDimens[4] == c && boardInOneDimens[0] == boardInOneDimens[4]
        && boardInOneDimens[0] == boardInOneDimens[8]) return true;

    if (boardInOneDimens[4] == c && boardInOneDimens[2] == boardInOneDimens[4]
        && boardInOneDimens[2] == boardInOneDimens[6]) return true;

    return false;
}

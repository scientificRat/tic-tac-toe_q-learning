//
//  MinimaxMachine.cpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by MichaelChen on 16/5/26.
//  Copyright © 2016年 黄正跃. All rights reserved.
//

#include "MinimaxMachine.h"
#include "Chessboard.h"

int MinimaxMachine::takeTurn(GameBoard *g) {
    ChessBoard *cb = new ChessBoard();
    int p1=0, p2=0;
    for (int i=0; i<g->getLength(); i++) {
        if (g->getState(i)==cst::PLAYER1_CHESS) p1++;
        if (g->getState(i)==cst::PLAYER2_CHESS) p2++;
    }
    if (p1==p2) {
        for (int i=0; i<g->getLength(); i++) {
            if (g->getState(i)==cst::PLAYER1_CHESS) cb->placeComp(i);
            if (g->getState(i)==cst::PLAYER2_CHESS) cb->placeHuman(i);
        }
    }
    if (p1>p2) {
        for (int i=0; i<g->getLength(); i++) {
            if (g->getState(i)==cst::PLAYER2_CHESS) cb->placeComp(i);
            if (g->getState(i)==cst::PLAYER1_CHESS) cb->placeHuman(i);
        }
    }
    int bestMove =0;
    int value = 0;
    int count=0;
    findCompMove(*cb, bestMove,value,count,CompLoss,CompWin);
    //printf("哈哈：%d\n",count);
    //delete &cb;
    return bestMove;
}

void MinimaxMachine::findCompMove(ChessBoard &board, int &bestMove, int &value, int &count,int alpha, int beta) {
    if (board.isFull()) {
        value = Draw;
    } else if (board.compCanWinImmediately(bestMove)) {
        value = CompWin;
    } else {
        value = alpha;
        for (int i = 0; i < 9 && value < beta; ++i) {
            if (board.isEmpty(i)) {
                board.placeComp(i);
                
                int tmp = -1, response = -1;  // Tmp is useless
                findHumanMove(board,tmp,response,count,value, beta);
                
                board.unPlace(i);
                
                if (response > value) {
                    value = response;
                    bestMove = i;
                }
            }else
                count++;
        }
    }
}

void MinimaxMachine::findHumanMove(ChessBoard &board, int &bestMove,int &value,int &count,int alpha, int beta) {
    if (board.isFull()) {
        value = Draw;
    } else if (board.humanCanWinImmediately(bestMove)) {
        value = CompLoss;
    } else {
        value = beta;
        for (int i = 0; i < 9 && value > alpha; ++i) {
            if (board.isEmpty(i)) {
                board.placeHuman(i);
                
                int tmp = -1, response = -1;  // Tmp is useless
                findCompMove(board,tmp,response,count,alpha,value);
                
                board.unPlace(i);
                
                if (response < value) {
                    value = response;
                    bestMove = i;
                }
            }else
                count++;
        }
    }
}
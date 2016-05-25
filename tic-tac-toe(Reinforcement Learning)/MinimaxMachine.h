//
//  MinimaxMachine.hpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by MichaelChen on 16/5/26.
//  Copyright © 2016年 黄正跃. All rights reserved.
//

#ifndef MinimaxMachine_h
#define MinimaxMachine_h

#include "Player.h"
#include "BaseDataStruct.h"
#include "Chessboard.h"

class MinimaxMachine:public Player {
private:
    std::string name;
    
    static const int CompWin = 2;
    static const int Draw = 1;
    static const int CompLoss = 0;
    
    void findCompMove(ChessBoard &board, int &bestMove, int &value, int &count,int alpha, int beta);
    void findHumanMove(ChessBoard &board, int &bestMove,int &value,int &count,int alpha, int beta);
    int getGameState();
    
public:
    MinimaxMachine(std::string _name)
    :name(_name)
    {
        
    }
    
    int takeTurn(GameBoard* g) override;
    
    void recieveFeedBack(FeedBack* f) override{

    }
    std::string getName() override{
        return name;
    }

};

#endif /* MinimaxMachine_h */

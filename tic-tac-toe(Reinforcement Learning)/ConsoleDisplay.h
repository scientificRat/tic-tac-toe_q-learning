//
//  ConsoleDisplay.h
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/22/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef ConsoleDisplay_h
#define ConsoleDisplay_h
#include "BaseDataStruct.h"
#include "Display.h"
#include <iostream>
using namespace std;
class ConsoleDisplay:public Display{
private:
    char player1_ch;
    char player2_ch;
public:
    ConsoleDisplay(char p1symbol,char p2symbol)
    :player1_ch(p1symbol),player2_ch(p2symbol){
    }
    
    void showGameStart(GameBoard*g) override;
    
    void printBoard(GameBoard*g) override;
    
    void printGameOver(GameBoard* g,int gameState) override;
    
    void showSystemMessage(std::string msg) override{
        cout<<msg;
    }
    
};

#endif /* ConsoleDisplay_h */

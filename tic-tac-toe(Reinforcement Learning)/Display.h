//
//  Display.h
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/22/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//




//This is a interface that any dispaly should implement!!!!!!


#ifndef Display_h
#define Display_h
#include "BaseDataStruct.h"
#include <string>

class Display{
public:

    virtual void printBoard(GameBoard*g)    =0;
    
    virtual void printGameOver(GameBoard* g,int gameState)  =0;
    
    virtual void showSystemMessage(std::string msg) =0;
    
};

#endif /* Display_h */

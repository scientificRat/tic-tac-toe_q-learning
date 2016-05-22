//
//  main.cpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include <iostream>
#include "Player.h"
#include "HumanPlayer.h"
#include "GameManager.h"
#include "ConsoleDisplay.h"
using namespace std;

int main(int argc, const char * argv[]) {
    GameBoard* gameBoard=new GameBoard(3,3);
    Player *p1=new HumamPlayer("player1");
    Player *p2=new HumamPlayer("palyer2");
    ConsoleDisplay* display=new ConsoleDisplay('X','O');
    GameManager *m=GameManager::create(display,gameBoard, 3, p1, p2);
    
    while(!m->isGameOver()){
        m->runOneTurn();
    }
    
    delete gameBoard;
    delete p1;
    delete p2;
    return 0;
}

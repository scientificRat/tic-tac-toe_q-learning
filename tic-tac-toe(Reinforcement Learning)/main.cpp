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
#include "QlearningMachine.h"
#include "GameManager.h"
#include "ConsoleDisplay.h"

namespace gameSettings {
    double epsilon=0;
    double alpaha=0.5;
    double discount=0.8;
}
using namespace std;
int main(int argc, const char * argv[]) {
    GameBoard* gameBoard=new GameBoard(3,3);
    Player *p1=new HumamPlayer("player1");
    Player *p2=new HumamPlayer("palyer2");
    Player *p_machine1=new QlearningMachine("playerS",gameSettings::epsilon,gameSettings::alpaha,gameSettings::discount);
    Player *p_machine2=new QlearningMachine("playerM",gameSettings::epsilon,gameSettings::alpaha,gameSettings::discount);
    ConsoleDisplay* display=new ConsoleDisplay('X','O');
    GameManager *m=GameManager::create(display,gameBoard, 3, p_machine1, p_machine2);
    m->runGameWithoutDisplay(20000);
    m->setPlayer(p_machine1, p2);
    m->runGame(2);
    delete gameBoard;
    delete p1;
    delete p2;
    return 0;
}

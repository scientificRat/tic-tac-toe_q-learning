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
#include "MinimaxMachine.h"
#include "RandomMachine.h"
#include "GameManager.h"
#include "ConsoleDisplay.h"

namespace gameSettings {
    double epsilon=0.5;
    double alpaha=0.3;
    double discount=0.8;
}
using namespace std;
int main(int argc, const char * argv[]) {
    GameBoard* gameBoard=new GameBoard(3,3);
    Player *p1=new HumamPlayer("player1");
    Player *p2=new HumamPlayer("palyer2");
    QlearningMachine *p_machine1=new QlearningMachine("playerS",gameSettings::epsilon,gameSettings::alpaha,gameSettings::discount);
    QlearningMachine *p_machine2=new QlearningMachine("playerM", gameSettings::epsilon,gameSettings::alpaha,gameSettings::discount);
    Player *p_minimax=new MinimaxMachine("player_minimax");
    Player *p_random=new RandomMachine("player_random");
    ConsoleDisplay* display=new ConsoleDisplay('X','O');
    GameManager *m=GameManager::create(display,gameBoard, 3, p_machine1, p_random);
    
    double temp_alpha = 1;
    for (int i=1; i<=100; i++) {
        temp_alpha *= 0.8;
        cout<<i<<' '<<temp_alpha<<endl;
        
        p_machine1->setAlpha(temp_alpha);
        p_machine2->setAlpha(temp_alpha);
        p_machine1->setEpsilon(1);
        p_machine2->setEpsilon(1);
        m->setPlayer(p_machine1, p_machine2);
        m->runGameWithoutDisplay(100);
        
        p_machine1->setEpsilon(0);
        m->setPlayer(p_machine1, p_minimax);
        m->runGameWithResultOnly(100);
        
        p_machine2->setEpsilon(0);
        m->setPlayer(p_minimax, p_machine2);
        m->runGameWithResultOnly(100);
    }
    
    delete gameBoard;
    delete p1;
    delete p2;
    delete p_machine1;
    delete p_machine2;
    delete p_minimax;
    delete p_random;
    return 0;
}

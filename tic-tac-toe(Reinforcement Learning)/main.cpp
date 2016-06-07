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
    //GameBoard* gameBoard=new GameBoard(3,3);
    GameBoard* gameBoard=new GameBoard(5,5);
    HumamPlayer *p1=new HumamPlayer("player1");
    HumamPlayer *p2=new HumamPlayer("palyer2");
    QlearningMachine *p_machine1=new QlearningMachine("playerS",gameSettings::epsilon,gameSettings::alpaha,gameSettings::discount);
    QlearningMachine *p_machine2=new QlearningMachine("playerM", gameSettings::epsilon,gameSettings::alpaha,gameSettings::discount);
    MinimaxMachine *p_minimax=new MinimaxMachine("player_minimax");
    RandomMachine *p_random=new RandomMachine("player_random");
    ConsoleDisplay* display=new ConsoleDisplay('X','O');
    //GameManager *m=GameManager::create(display,gameBoard, 3, p_machine1, p_random);
    GameManager *m=GameManager::create(display,gameBoard, 4, p_machine1, p_random);
    /*
    double alpha = 1;
    double epsilon = 0.3;
    double discount = 0.8;
    int total1, total2;
    
    p_machine1->setDiscount(discount);
    for (int i=1; i<=500; i++) {
        alpha *= 0.98;
        cout << "round " << i << " \t";
        total1 = 0;
        total2 = 0;
        for (int j=0; j<100; j++) {
            p_machine1->setAlpha(alpha);
            p_machine1->setEpsilon(epsilon);
            m->setPlayer(p_machine1, p_random);
            m->runGameWithoutDisplay(1);
            m->setPlayer(p_random, p_machine1);
            m->runGameWithoutDisplay(1);
            
            p_machine1->setAlpha(0);
            p_machine1->setEpsilon(0);
            m->setPlayer(p_machine1, p_minimax);
            total1 += m->runGameWithResultOnly(1);
            m->setPlayer(p_minimax, p_machine1);
            total2 += m->runGameWithResultOnly(1);
        }
        cout << total1 << "  " << total2 << endl;
        
    }*/
    
//    m->setPlayer(p_machine1, p2);
//    m->runGame(3);
//    m->setPlayer(p1, p_machine1);
//    m->runGame(3);
    
    m->setPlayer(p1, p_minimax);
    m->setPlayer(p1, p2);
    m->runGame(3);
    
    delete gameBoard;
    delete p1;
    delete p2;
    delete p_machine1;
    delete p_machine2;
    delete p_minimax;
    delete p_random;
    return 0;
}

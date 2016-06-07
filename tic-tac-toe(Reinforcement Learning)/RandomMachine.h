//
//  RandomMachine.h
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by MichaelChen on 16/5/30.
//  Copyright © 2016年 黄正跃. All rights reserved.
//

#ifndef RandomMachine_h
#define RandomMachine_h

#include "Player.h"
#include "BaseDataStruct.h"
#include <string>
#include <iostream>
#include <ctime>
#include <random>
using namespace std;

class RandomMachine:public Player{
private:
    std::string name;
public:
    RandomMachine(std::string _name)
    :name(_name)
    {
    }
    
    int takeTurn(GameBoard* g) override {
        static std::default_random_engine randEngine(static_cast<int>(time(0)));
        static std::uniform_int_distribution<int> I(0,40319);
        int temp;
        while (1) {
            temp = I(randEngine) % g->getLength();
            if (g->getState(temp)==cst::NO_CHESS) {
                return temp;
            }
        }
    }
    
    void recieveFeedBack(FeedBack* f) override{
        
    }
    std::string getName() override{
        return name;
    }
    
    
};

#endif /* RandomMachine_h */

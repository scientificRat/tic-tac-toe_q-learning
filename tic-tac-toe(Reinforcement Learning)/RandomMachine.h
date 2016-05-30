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
class RandomMachine:public Player{
private:
    std::string name;
public:
    RandomMachine(std::string _name)
    :name(_name)
    {
        srand((unsigned int)time(NULL));
    }
    
    int takeTurn(GameBoard* g) override {
        int temp;
        while (1) {
            temp = rand()%g->getLength();
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

//
//  HumanPlayer.h
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef HumanPlayer_h
#define HumanPlayer_h
#include "Player.h"
#include <string>
#include <iostream>
class HumamPlayer:public Player{
private:
    std::string name;
public:
    HumamPlayer(std::string _name)
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

#endif /* HumanPlayer_h */

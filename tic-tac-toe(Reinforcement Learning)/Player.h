//
//  Player.h
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include "BaseDataStruct.h"
//player interface
class Player{
public:
    virtual int takeTurn(GameBoard* g) =0;
    virtual void recieveFeedBack(FeedBack* f) =0;
    virtual std::string getName() =0;
};

#endif /* Player_h */

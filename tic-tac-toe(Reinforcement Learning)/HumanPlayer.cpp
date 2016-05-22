//
//  HumanPlayer.cpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include "HumanPlayer.h"
int HumamPlayer::takeTurn(GameBoard *g){
    int length=g->getHeight()*g->getWidth();
    bool valid[length];
    for(int i=0;i<length;i++){
        if(g->getState(i)==cst::NO_CHESS){
            valid[i]=true;
        }
        else{
            valid[i]=false;
        }
    }
    int choice;
    std::cout<<name<<"please take the turn\n>>>";
    while (true) {
        std::cin>>choice;
        if(choice>=0 && choice<length){
            break;
        }
        std::cout<<"wrong choice\ninput again>>> ";
        std::cin.clear();
        
    }
    return choice;
}
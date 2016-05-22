//
//  GameManager.cpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include "GameManager.h"
//single instance
GameManager* GameManager::gamemanager=nullptr;

//check the map state; return 1 when player1 win ; 2 when player2 win ;0 no-win-lose ;
int GameManager::check(){
    int width=gameboard->getWidth();
    int height=gameboard->getHeight();
    int state=0;
    int countPlayer1=0;
    int countPlayer2=0;
    int result=0;
    //check rows
    for(int i=0;i<height;i++){
        state=0;
        countPlayer1=0;
        countPlayer2=0;
        for(int j=0;j<width;j++){
            result=checkHelp(state, countPlayer1, countPlayer2, i, j);
            if(0==result){
                continue;
            }
            else{
                return result;
            }
        }
    }
    //check colums
    for(int j=0;j<width;j++){
        state=0;
        countPlayer1=0;
        countPlayer2=0;
        for(int i=0;i<height;i++){
            result=checkHelp(state, countPlayer1, countPlayer2, i, j);
            if(0==result){
                continue;
            }
            else{
                return result;
            }
        }
    }

    //check diagonal
    for(int m=winStateNumOfChess-width;m<=height-winStateNumOfChess;m++){
        state=0;
        countPlayer1=0;
        countPlayer2=0;
        for(int j=0;j<width;j++){
            int i=m+j;
            if(i<0 || i > height){
                continue;
            }
            result=checkHelp(state, countPlayer1, countPlayer2, i,j);
            if(0==result){
                continue;
            }
            else{
                return result;
            }
        }
    }
    //check reverse-diagonal
    for(int m=winStateNumOfChess-1;m<=width+height-winStateNumOfChess-1;m++){
        state=0;
        countPlayer1=0;
        countPlayer2=0;
        for(int j=0;j<width;j++){
            int i=m+j;
            if(i<0 || i> height){
                continue;
            }
            result=checkHelp(state, countPlayer1, countPlayer2, i,j);
            if(0==result){
                continue;
            }
            else{
                return result;
            }
        }
        
    }
    
    
    return 0;
}


int GameManager::checkHelp(int &state, int &countPlayer1, int &countPlayer2,int &i,int &j){
    
    const int ON_BLANK=0;
    const int ON_PLAYER1=1;
    const int ON_PLAYER2=2;
    
    if(cst::NO_CHESS==gameboard->getState(i, j)){
        switch (state) {
            case ON_PLAYER1:
                state=ON_BLANK;
                countPlayer1=0;
                break;
            case ON_PLAYER2:
                state=ON_BLANK;
                countPlayer2=0;
                break;
        }
    }
    else if(cst::PLAYER1_CHESS==gameboard->getState(i, j)){
        switch (state) {
            case ON_BLANK:
                state=ON_PLAYER1;
                ++countPlayer1;
                break;
            case ON_PLAYER1:
                ++countPlayer1;
                if(countPlayer1 == winStateNumOfChess){
                    return 1;
                }
                break;
            case ON_PLAYER2:
                state=ON_PLAYER1;
                countPlayer2=0;
                ++countPlayer1;
                break;
        }
    }
    else if(cst::PLAYER2_CHESS==gameboard->getState(i, j)){
        switch (state) {
            case ON_BLANK:
                state=ON_PLAYER2;
                ++countPlayer2;
                break;
            case ON_PLAYER1:
                state=ON_PLAYER2;
                countPlayer1=0;
                ++countPlayer2;
                break;
            case ON_PLAYER2:
                ++countPlayer2;
                if(countPlayer2 == winStateNumOfChess){
                    return 2;
                }
                break;
        }
    }
    
    return 0;
}



void GameManager::doGameOver(){
    display->printGameOver(gameboard, gameState);
    gameboard=nullptr;
    gameOver=true;
}


void GameManager::runOneTurn(){
    int state=0;
    int action=0;
    FeedBack *f=nullptr;

    display->printBoard(gameboard);
    
    while(true){
        action=player1->takeTurn(this->gameboard);
        if(gameboard->tryApplyAction(action, 1)){
            break;
        }
        display->showSystemMessage(player1->getName()+"wrong action!");
    }
    
    state=check();
    f=new FeedBack(state,state,action);
    player2->recieveFeedBack(f);
    delete f;
    step++;
    if(state!=0 || step == gameboard->getLength()){
        gameState=state;
        doGameOver();
        return;
    }
    
    display->printBoard(gameboard);
    while(true){
        action=player2->takeTurn(this->gameboard);
        if(gameboard->tryApplyAction(action, 2)){
            break;
        }
        display->showSystemMessage(player2->getName()+"wrong action!");
    }
    state=check();
    f=new FeedBack(state,state,action);
    player1->recieveFeedBack(f);
    delete f;
    step++;
    if(state!=0 || step == gameboard->getLength()){
        gameState=state;
        doGameOver();
        return;
    }
    
    display->printBoard(gameboard);
    
}

void GameManager::restartGame(){
    gameboard->reset();
    //imcompleted!
}

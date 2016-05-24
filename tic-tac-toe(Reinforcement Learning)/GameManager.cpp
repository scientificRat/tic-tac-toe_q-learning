//
//  GameManager.cpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include "GameManager.h"
//#include <iostream>
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
    
    static const int ON_BLANK=0;
    static const int ON_PLAYER1=1;
    static const int ON_PLAYER2=2;
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
                    return cst::PLAYER1_WIN;
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
                    return cst::PLAYER2_WIN;
                }
                break;
        }
    }
    
    return 0;
}

void GameManager::doGameOver(){
    double reward1;
    double reward2;
    if(cst::PLAYER1_WIN == gameState){
        reward1=10;
        reward2=-10;
    }
    else if(cst::PLAYER2_WIN ==gameState ){
        reward1=-10;
        reward2=10;
    }
    else{//if withdraw
        reward1=-10;
        reward2=-10;
    }
    FeedBack* f=new FeedBack(gameState,reward1,gameboard->getUniqueString());
    player1->recieveFeedBack(f);
    f->reward=reward2;
    player2->recieveFeedBack(f);
    delete f;
    if(displayOn) display->printGameOver(gameboard, gameState);
}

void GameManager::runOneTurn(){
    int state=0;
    int action=0;
    double reward=0;
    FeedBack *f=nullptr;
    //update display
    if(displayOn){
        display->printBoard(gameboard);
        display->showSystemMessage(player1->getName()+ " take the turn\n>>>");
    }
    
    while(true){
        action=player1->takeTurn(this->gameboard);
        if(gameboard->tryApplyAction(action, 1)) break;
        if(displayOn) display->showSystemMessage(player1->getName()+" wrong action!");
    }
    //check and sendFeedback
    state=check();
//    std::cerr<<"["<<state<<"]"<<std::endl;
    step++;
    if(state!=0 || step==gameboard->getLength()) gameState=state;
    
    if(gameState!=cst::GAME_NORMAL_RUN){
        doGameOver();
        return;
    }
    else{
        f=new FeedBack(gameState,reward,gameboard->getUniqueString());
        player2->recieveFeedBack(f);
        delete f;
    }
    
    //update display
    if(displayOn){
        display->printBoard(gameboard);
        display->showSystemMessage(player2->getName()+ " take the turn\n>>>");
    }
    
    while(true){
        action=player2->takeTurn(this->gameboard);
        if(gameboard->tryApplyAction(action, 2)) break;
        if(displayOn) display->showSystemMessage(player2->getName()+" wrong action!");
    }
    //check and sendFeedback
    state=check();
//    std::cerr<<"["<<state<<"]"<<std::endl;
    step++;
    if(state!=0 || step==gameboard->getLength()) gameState=state;
    
    if(gameState!=cst::GAME_NORMAL_RUN){
        doGameOver();
        return;
    }
    else{
        f=new FeedBack(gameState,reward,gameboard->getUniqueString());
        player1->recieveFeedBack(f);
        delete f;
    }
}

void GameManager::restartGame(){
    gameboard->reset();
    gameState=cst::GAME_NORMAL_RUN;
    step=0;
}

void GameManager::runGame(int times){
    displayOn=true;
    while(times--){
        display->showGameStart(gameboard);
        while(!this->isGameOver()){
            runOneTurn();
        }
        restartGame();
    }
}

void GameManager::runGameWithoutDisplay(int times){
    displayOn=false;
    while (times--) {
        while(!this->isGameOver()){
            runOneTurn();
        }
        restartGame();
    }
}


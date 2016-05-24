//
//  GameManager.h
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//
//   README : This class mantain the
#ifndef GameManager_h
#define GameManager_h
#include <stdexcept>
#include "Player.h"
#include "Display.h"
class GameManager{
private:
    //gameState is used when game is over which records who win
    int gameState=cst::GAME_NORMAL_RUN;
    int step=0;
    int winStateNumOfChess;
    
    
    GameBoard* gameboard;
    Player* player1;
    Player* player2;
    //the display device
    Display *display;
    bool displayOn=false;
    //single Instance
    static GameManager* gamemanager;
    
    //private constructor
    GameManager(Display * d,GameBoard* g,int _winStateNumOfChess,Player* _player1,Player* _palyer2)
    :
    display(d),
    gameboard(g),
    winStateNumOfChess(_winStateNumOfChess),
    player1(_player1),player2(_palyer2)
    {
        player1->setRole(1);
        player2->setRole(2);
    }
    
    void runOneTurn();
    
    //check now state
    int check();
    
    int checkHelp(int &state,int &countPlayer1,int &countPlayer2,int &i,int &j);
    
    bool isFull();
    
    bool isGameOver(){
        if(cst::GAME_NORMAL_RUN==this->gameState){
            return false;
        }
        else{
            return true;
        }
    }
    
    //call when game over
    void doGameOver();
    
    void restartGame();
    
public:
    
    static GameManager*create(Display * d,GameBoard* g,int _winStateNumOfChess,Player* _player1,Player* _palyer2){
        
        gamemanager=new GameManager(d,g,_winStateNumOfChess,_player1,_palyer2);
        if(nullptr==gamemanager){
            throw std::runtime_error("create Gamemanager failed!");
        }
        else{
            return gamemanager;
        }
    }

    static GameManager*getInstance(){
        if(nullptr == gamemanager){
            throw std::runtime_error("get GameManager before created!");
        }
        else{
            return gamemanager;
        }
        
    }
    
    void setPlayer(Player* _player1,Player* _palyer2){
        this->player1=_player1;
        this->player2=_palyer2;
        player1->setRole(1);
        player2->setRole(2);
    }

    void runGame(int times);
    //call when you just want to train machine
    void runGameWithoutDisplay(int times);
    
    
};

#endif /* GameManager_h */

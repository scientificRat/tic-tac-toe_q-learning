//
//  BaseDataStruct.h
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef BaseDataStruct_h
#define BaseDataStruct_h
#include <string>
#include <sstream>
namespace cst {
    const int NO_CHESS=0;
    const int PLAYER1_CHESS=1;
    const int PLAYER2_CHESS=1;
}

struct GameBoard{
private:
    int width;
    int height;
    int length;
    int *vect;
    
public:
    
    GameBoard(int _width,int _height)
    :width(_width),
    height(_height){
        length=width*height;
        vect=new int[length];
        for(int i=0;i<length;i++){
            vect[i]=0;
        }
        
    }
    
    GameBoard(GameBoard*g){
        this->width=g->getWidth();
        this->height=g->getHeight();
        int lenth=width*height;
        vect=new int[lenth];
        for(int i=0;i<lenth;i++){
            vect[i]=g->getState(i);
        }
    }
    
    
    bool operator < (const GameBoard&g) const{
        int len=width*height;
        for(int i=0;i<len;i++){
            if(this->vect[i]<g.vect[i]){
                return true;
            }
            else if(this->vect[i]>g.vect[i]){
                return false;
            }
        }
        return false;
    }
    
    bool operator ==(const GameBoard& g) const{
        int len=width*height;
        for(int i=0;i<len;i++){
            if(this->vect[i]!=g.vect[i]){
                return false;
            }
        }
        return true;
    }
    
    std::string getUniqueString(){
        std::string result;
        std::stringstream ss;
        for(int i=0;i<length;i++){
            ss<<vect[i];
        }
        ss>>result;
        return result;
    }
    
    int getWidth(){
        return this->width;
    }
    
    int getHeight(){
        return this->height;
    }
    
    int getState(int row,int col){
        return vect[row*width+col];
    }
    
    int getState(int index){
        return vect[index];
    }
    
    int getLength(){
        return length;
    }
    
    bool tryApplyAction(int pos,int role){
        if(0==vect[pos] && pos>=0 && pos<length){
            vect[pos]=role;
            return true;
        }
        else{
            return false;
        }
        
    }
    
    void reset(){
        for(int i=0;i<length;i++){
            vect[i]=0;
        }
    }
    
    ~GameBoard(){
        delete vect;
    }
    
};

struct FeedBack{
public:
    int gameState;
    int reward;
    int oppoentStep;
    FeedBack(int _gameState,int _reward,int _oppoentStep)
    :gameState(_gameState),reward(_reward),oppoentStep(_oppoentStep){
    }
};



#endif /* BaseDataStruct_h */

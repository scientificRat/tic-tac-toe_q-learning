//
//  QlearningMachine.cpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include "QlearningMachine.h"
#include <iostream>
#include <fstream>
#include <random>
using namespace std;
////private:
//---------------------------------------------------------------------
//---------FOLLOWINGS ARE THE KERNEL ALGORITHM OF Q-LEARNING-----------
//---------------------------------------------------------------------
int QlearningMachine::getPolicy(std::string& gameBoardIdentifier){
    int policy=-1;
    double maxQvalue=-INFINITY;
    bool isFirst=true;
    double qValue;
    //Traversal the board and find the max q-value's action among the valid actions
    
    for(int i=0;i<gameBoardIdentifier.length();i++){
        if('0'==gameBoardIdentifier[i]){
            std::string tempString=gameBoardIdentifier;
            tempString[i]=getRole()+'0';
            if(isFirst){
                policy=i;
                if(afterStateMap.count(tempString)){
                    maxQvalue=afterStateMap[tempString];
                }
                else{
                    maxQvalue=0;
                }
                isFirst=false;
            }
            else{
                if(afterStateMap.count(tempString)){
                    qValue=afterStateMap[tempString];
                }
                else{
                    qValue=0;
                }
                if(qValue>maxQvalue){
                    maxQvalue=qValue;
                    policy=i;
                }
            }
        }
    }
    
    return policy;
}

int QlearningMachine::makeActionDecision(std::string& gameBoardIdentifier){
    int action=-1;
    static std::default_random_engine randEngine(static_cast<int>(time(0)));
    static std::bernoulli_distribution T(1-epsilon);
    static std::uniform_int_distribution<int> I(0,65532);
    //about (1-epsilon) T wiil return true
    if(T(randEngine)){
        action=getPolicy(gameBoardIdentifier);
    }
    else{
        vector<int> validStates;
        for(int i=0;i<gameBoardIdentifier.size();i++){
            if('0'==gameBoardIdentifier[i]) validStates.push_back(i);
        }
        action=validStates[I(randEngine) % validStates.size()];
    }
    return action;
}

void QlearningMachine::upDateValue(FeedBack* f){
    double& qValue=afterStateMap[presentAfterState];
    double sample;
    //if game end
    if(f->gameState!=cst::GAME_NORMAL_RUN){
        sample=f->reward;
    }
    else{
        sample=f->reward+discount*getMaxQvalue(f->gameBoardIdentifier);
    }
    qValue=(1-alpha)*qValue+alpha*sample;
    if (presentAfterState.compare("010000000")==0) {
        cout<<qValue<<endl;
    }
    
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------


/////public:
//@override   callBack Function
int QlearningMachine::takeTurn(GameBoard *g){
    step++;
    //if (step==1) return 4;
    alpha = pow((double)1/step, (double)0.5);
    //alpha = 0.5;
    //cout<<afterStateMap<<endl;
    if (step>20000) {
//        alpha = 0;
//        epsilon = 0;
    }
    std::string gameBaordIdentifier=g->getUniqueString();
    int action=makeActionDecision(gameBaordIdentifier);
    presentAfterState=gameBaordIdentifier;
    presentAfterState[action]='0'+getRole();
    return action;
}
//@override   callBack Function
void QlearningMachine::recieveFeedBack(FeedBack *f){
    upDateValue(f);
    //if gameover
    if(cst::GAME_NORMAL_RUN!=f->gameState){
        doOneGameOver();
    }
}

void QlearningMachine::saveValuesToDisk(std::string fileName){
    
}

void QlearningMachine::resumeFromDisk(std::string fileName){
    
}

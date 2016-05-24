//
//  QlearningMachine.cpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include "QlearningMachine.h"
#include <fstream>
#include <random>
using namespace std;
////private:
//---------------------------------------------------------------------
//---------FOLLOWINGS ARE THE KERNEL ALGORITHM OF Q-LEARNING-----------
//---------------------------------------------------------------------
int QlearningMachine::getPolicy(std::string& gameBoardIdentifier){
    int policy=-1;
    int tempAction=0;
    double maxQvalue=-INFINITY;
    bool isFirst=true;
    //Traversal the board and find the max q-value's action among the valid actions
    for(int i=0;i<gameBoardIdentifier.size();i++){
        if('0'==gameBoardIdentifier[i]){
            std::string tempString=gameBoardIdentifier;
            tempString[i]=getRole()+'0';
            if(isFirst){
                policy=i;
                //if no maped value, we will get null (0)
                maxQvalue=afterStateMap[tempString];
                isFirst=false;
            }
            else{
                double qValue=afterStateMap[tempString];
                if(qValue>maxQvalue){
                    maxQvalue=qValue;
                    policy=tempAction;
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
    
    
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------


/////public:
//@override   callBack Function
int QlearningMachine::takeTurn(GameBoard *g){
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

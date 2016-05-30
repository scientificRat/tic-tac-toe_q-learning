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
    static std::uniform_real_distribution<double> R(0,1);
    static std::uniform_int_distribution<int> I(0,40319);
    //about (1-epsilon) T wiil return true
    if(R(randEngine)>epsilon){
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
    /*
    if (machineName.compare("playerS")==0){
        if (presentAfterState.compare("100000000")==0) {
            valueTable[0]=qValue;
        }
        if (presentAfterState.compare("010000000")==0) {
            valueTable[1]=qValue;
        }
        if (presentAfterState.compare("001000000")==0) {
            valueTable[2]=qValue;
        }
        if (presentAfterState.compare("000100000")==0) {
            valueTable[3]=qValue;
        }
        if (presentAfterState.compare("000010000")==0) {
            valueTable[4]=qValue;
        }
        if (presentAfterState.compare("000001000")==0) {
            valueTable[5]=qValue;
        }
        if (presentAfterState.compare("000000100")==0) {
            valueTable[6]=qValue;
        }
        if (presentAfterState.compare("000000010")==0) {
            valueTable[7]=qValue;
        }
        if (presentAfterState.compare("000000001")==0) {
            valueTable[8]=qValue;
        }
    }
    */
    
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
        /*
        step++;
        if (machineName.compare("playerS")==0){
            int max = 0;
            for (int i=0; i<9; i++) {
                if (valueTable[i] > valueTable[max])
                    max = i;
            }
            cout<<step<<' '<<alpha<<' '<<epsilon<<' '<<max<<endl;
            cout<<valueTable[0]<<' '<<valueTable[1]<<' '<<valueTable[2]<<endl;
            cout<<valueTable[3]<<' '<<valueTable[4]<<' '<<valueTable[5]<<endl;
            cout<<valueTable[6]<<' '<<valueTable[7]<<' '<<valueTable[8]<<"\n\n"<<endl;
        }*/
    }
}

void QlearningMachine::saveValuesToDisk(std::string fileName){
    
}

void QlearningMachine::resumeFromDisk(std::string fileName){
    
}

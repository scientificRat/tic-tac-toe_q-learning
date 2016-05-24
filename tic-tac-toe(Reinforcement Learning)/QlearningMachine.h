//
//  QlearningMachine.h
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/17/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef QlearningMachine_h
#define QlearningMachine_h
#include "Player.h"
#include "BaseDataStruct.h"
#include <string>
#include <unordered_map>
#include <vector>
class QlearningMachine:public Player{
private:
    std::string machineName;
    double epsilon;
    double alpha;
    double discount;
    
    std::unordered_map<std::string, double> afterStateMap;
    
    std::string presentAfterState;
    
    int getPolicy(std::string& gameBoardIdentifier);
    
    double getMaxQvalue(std::string gameBoardIdentifier){
        gameBoardIdentifier[ getPolicy(gameBoardIdentifier) ]='0'+getRole();
        return afterStateMap[gameBoardIdentifier];
    }
    
    int makeActionDecision(std::string& gameBoardIdentifier);
    
    void upDateValue(FeedBack* f);
    
    void doOneGameOver(){
        presentAfterState="";
    }
    
public:
    QlearningMachine(std::string name,double _epsilon,double _alpha,double _discount)
    :machineName(name),
    epsilon(_epsilon),
    alpha(_alpha),
    discount(_discount){}
    
    int takeTurn(GameBoard* g) override;
    
    void recieveFeedBack(FeedBack* f) override;
    
    void saveValuesToDisk(std::string fileName);
    
    void resumeFromDisk(std::string fileName);
    
    std::string getName() override{
        return machineName;
    }
    
    void setEpsilon(double _epsilon){
        this->epsilon=_epsilon;
    }
    void setAlpha(double _alpha){
        this->alpha=_alpha;
    }
    void setDiscount(double _discount){
        this->discount=_discount;
    }
    
};

#endif /* QlearningMachine_h */

//
//  DataCollection.h
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by MichaelChen on 16/5/26.
//  Copyright © 2016年 黄正跃. All rights reserved.
//

#ifndef DataCollection_h
#define DataCollection_h

#include "BaseDataStruct.h"
#include <iostream>

#define TOTAL 10

class DataCollection {
private:
    int arr[TOTAL];
    int curr = 0;
    
    void getAvg() {
        int p1w=0, p2w=0, withdraw=0;
        for (int i=0; i<TOTAL; i++) {
            switch (arr[i]) {
                case 1:
                    p1w++;
                    break;
                case 2:
                    p2w++;
                    break;
                case 0:
                    withdraw++;
                    break;
                default:
                    break;
            }
        }
        //std::cout << p1w << " " << withdraw << " " << p2w << std::endl;
        std::cout << curr << "\t\t";
        for (int i=0; i<withdraw; i++) {
            std::cout<<' ';
        }
        std::cout<<'|'<<std::endl;
    }
    
public:
    DataCollection() {
    }
    
    ~DataCollection() {
    }
    
    void addNewRseult(int gameState) {
        arr[curr%TOTAL] = gameState;
        if ((++curr)>=TOTAL) getAvg();
    }
};

#endif /* DataCollection_h */

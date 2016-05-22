//
//  ConsoleDisplay.cpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/22/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include "ConsoleDisplay.h"
void ConsoleDisplay::printBoard(GameBoard *g){
    int width=g->getWidth();
    int height=g->getHeight();
    int length=width*height;
    char square[length];
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if (g->getState(i, j)==0) {
                square[i*width+j]='0'+i*width+height;
            }
            
        }
    }
    
    for(int i=0;i<length;i++){
        
        switch (g->getState(i)) {
            case 0:
                square[i]='0'+i;
                break;
            case 1:
                square[i]=player1_ch;
                break;
            case 2:
                square[i]=player2_ch;
                break;
        }
        
        
    }
    
    cout << "Player 1 ("<<player1_ch<<")  -  Player 2 ("<<player2_ch<<")" << endl << endl;
    cout << endl;
    
    cout << "     |     |     " << endl;
    cout << "  " << square[0] << "  |  " << square[1] << "  |  " << square[2] << endl;
    
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    
    cout << "  " << square[3] << "  |  " << square[4] << "  |  " << square[5] << endl;
    
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    
    cout << "  " << square[6] << "  |  " << square[7] << "  |  " << square[8] << endl;
    
    cout << "     |     |     " << endl << endl;
    
    
}

void ConsoleDisplay::printGameOver(GameBoard* g,int gameState){
    if(gameState==0){
        std::cout<<"Withdraw\n";
    }
    else if(gameState==1){
        std::cout<<"player1 win"<<std::endl;
    }
    else if(gameState==2){
        std::cout<<"palyer2 win"<<std::endl;
    }
    printBoard(g);
}
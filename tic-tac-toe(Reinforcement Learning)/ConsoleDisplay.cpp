//
//  ConsoleDisplay.cpp
//  tic-tac-toe(Reinforcement Learning)
//
//  Created by 黄正跃 on 5/22/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include "ConsoleDisplay.h"
#include <unistd.h>

void ConsoleDisplay::showGameStart(GameBoard *g){
    cout<<"----------------------------------\n";
    cout<<"============NEW==GAME=============\n";
    cout<<"----------------------------------\n";
}

void ConsoleDisplay::printBoard(GameBoard *g){
    int width=g->getWidth();
    int height=g->getHeight();
    int length=width*height;
    char square[length];
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if (g->getState(i, j)==0) {
                square[i*width+j]='0'+(i*width+height)%10;
            }
            
        }
    }
    
    for(int i=0;i<length;i++){
        
        switch (g->getState(i)) {
            case 0:
                square[i]='0'+i%10;
                break;
            case 1:
                square[i]=player1_ch;
                break;
            case 2:
                square[i]=player2_ch;
                break;
        }
        
        
    }
    
    if (length==9) {
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
        
    } else if (length==25) {
        
        cout << "Player 1 ("<<player1_ch<<")  -  Player 2 ("<<player2_ch<<")" << endl << endl;
        cout << endl;
        
        for (int i=0; i<25; i++) {
            cout << square[i];
            if (i%5==4)  cout << "\n";
            else cout << "\t";
            
        }
    }
    
    
    
}

void ConsoleDisplay::printGameOver(GameBoard* g,int gameState){
    printBoard(g);
    if(gameState==cst::WITHDRAW){
        std::cout<<"Withdraw\n";
    }
    else if(gameState==cst::PLAYER1_WIN){
        std::cout<<"Player1("<<player1_ch<<") win"<<std::endl;
    }
    else if(gameState==cst::PLAYER2_WIN){
        std::cout<<"Palyer2("<<player2_ch<<") win"<<std::endl;
    }
    std::cout<<"--------------------------\n\n";
    
}

void ConsoleDisplay::printGameResult(int gameState) {
    if(gameState==cst::WITHDRAW){
        std::cout<<"Withdraw\n";
    }
    else if(gameState==cst::PLAYER1_WIN){
        std::cout<<"Player1("<<player1_ch<<") win"<<std::endl;
    }
    else if(gameState==cst::PLAYER2_WIN){
        std::cout<<"Palyer2("<<player2_ch<<") win"<<std::endl;
    }
}
#include <iostream>
#include "Board.h"
#include "Board.cpp"



int main() {
    Board game;

    game.startGame();
}




void debug(){
    Board game1;
    game1.putChecker(1);
    game1.putChecker(1);
    game1.putChecker(1);
    game1.putChecker(1);
    game1.putChecker(1);
    game1.putChecker(1);
    game1.putChecker(1);
    game1.putChecker(2);
    game1.getBoard();

    // test colConnect4
    Board game2;
    game2.putChecker(1);
    game2.putChecker(1);
    game2.putChecker(1);
    game2. putChecker(2);
    game2. putChecker(3);
    game2. putChecker(2);
    game2. putChecker(3);
    game2. putChecker(2);
    game2. putChecker(3);
    game2. putChecker(2);
    game2. putChecker(3);
    game2. putChecker(2);
    game2. putChecker(2);
    game2.getBoard();

    if(game2.colConnect4()){
        std::cout << "colConnect4 pass test1";
    }


    game1.win();
    Board game3;
    game3.putChecker(1);
    game3.putChecker(2);
    game3.putChecker(3);
    game3.putChecker(4);
    game3.putChecker(5);
    game3.putChecker(6);
    game3.putChecker(7);
    game3.putChecker(1);
    game3.putChecker(4);
    game3.putChecker(1);
    game3.putChecker(5);
    game3.putChecker(1);
    game3.putChecker(6);
    game3.putChecker(1);
    game3.putChecker(7);
    game3.putChecker(1);
    game3.putChecker(5);
    game3.putChecker(6);
    game3.putChecker(6);
    game3.getBoard();
    if(game3.rowConnect4()){
        std::cout<< "rowConnect4 passed the test1" << std::endl;
    }

    if(game3.diagonalConnect4()){
        std::cout<< "diagonalConnect4 passed the test1"<< std::endl;
    }

    if(game3.win()) {
        std::cout <<"Win pass the test\n";
    }
}


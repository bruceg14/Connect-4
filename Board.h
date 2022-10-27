//
// Created by Bruce Guo on 10/19/22.
//

#ifndef CONNECT4_BOARD_H
#define CONNECT4_BOARD_H


#include <deque>

class Board {
public:
    Board();
    void getBoard();
    bool isFull();
    void loadGame(std::string fileName);
    bool putChecker(int column); //1 base index instead of 0
    void switchPlayer();
    bool win() const;
    bool colConnect4() const;
    bool rowConnect4() const;
    bool diagonalConnect4() const;
    void startGame();
    void process(std::string playerNo1, std::string playerNo2);
    void storeGame(std::string player1Name, std::string player2Name);
    bool regret1();


private:
    bool player1;
    bool player2;
    int gameBoard[6][7];
    int numChecker;
    std::deque<int> history;
};


#endif //CONNECT4_BOARD_H

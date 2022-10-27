//
// Created by Bruce Guo on 10/19/22.
//
#include <iostream>
#include <fstream>

#include "Board.h"
const int ROW = 6;
const int COL = 7;

Board::Board(): gameBoard(), numChecker(0), player1(true), player2(false), history(){
    for(int i(0); i < ROW; ++i){
        for(int j(0); j < COL; ++j){
            gameBoard[i][j] = 0;
        }
    }
}


void Board::getBoard() {
    for(int i(0); i < ROW; ++i){
        for(int j(0); j < COL; ++j){
            std::string tmp;
            if(gameBoard[i][j] == 0){
                tmp = " ";
            } else if(gameBoard[i][j] == 1){
                tmp = "r";
            } else {
                tmp = "y";
            }
            std::cout << "|" << tmp;
            if(j == COL - 1){
                std::cout <<"|\n";
            }
        }
    }
    std::cout << "\n";
}


bool Board::isFull() {
    return numChecker == ROW * COL;
}


void Board::loadGame(std::string fileName) {
    std::ifstream infile;
    infile.open(fileName);
    if (infile.fail()) {
        throw std::invalid_argument("Invalid Arg.");
    }

    int num(0);

    int tmp[6][7];
    int tmpCount(0);

    for (int i(0); i < ROW; ++i) {
        for (int j(0); j < COL; ++j) {
            infile >> num;
            if(num != 0){
                tmpCount++;
            }
            tmp[i][j] = num;
        }
    }

    std::swap(tmp, gameBoard);
    std::swap(tmpCount, numChecker);
    infile.close();
}


bool Board::putChecker(int column){
    if(column > 7){
        std::cout <<"Out of range!\n";
        return false;
    }
    --column;
    int playerNum;
    if(player1 == true){
        playerNum = 1;
    } else{
        playerNum = 2;
    }
    if(gameBoard[0][column] != 0){
        std::cout <<"This column is full!\n";
        return false;
    } else{
        for(int i(ROW - 1); i >= 0; --i){
            if(gameBoard[i][column] == 0){
                gameBoard[i][column] = playerNum;
                break;
            }
        }
        ++numChecker;
        history.push_back(column);
        switchPlayer();
        return true;
    }

}

void Board::switchPlayer() {
    if(player1 == true){
        player1 = false;
        player2 = true;
    } else{
        player1 = true;
        player2 = false;
    }
}

bool Board::win() const{
    return colConnect4() || rowConnect4() || diagonalConnect4();
}

bool Board::colConnect4() const{
    int checker = 1;
    for(int i(0); i < COL; ++i){
        for(int j(1); j < ROW; ++j){
            if (checker < 4){
                if(gameBoard[i][j] != 0 &&gameBoard[i][j] == gameBoard [i][j - 1]){
                    checker++;
                } else {
                    checker = 1;
                    if(j > ROW - 4 + 1){
                        break;
                    }
                }
            }
            if (checker >= 4){
                return true;
            }
        }
    }
    return false;
}

bool Board::rowConnect4() const {
    int checker = 1;
    for(int i(0); i < ROW; ++i){
        for(int j(1); j < COL; ++j){
            if (checker < 4){
                if(gameBoard[i][j] != 0 && gameBoard[i][j] == gameBoard [i][j - 1]){
                    checker++;
                } else {
                    checker = 1;
                    if(j > ROW - 4 + 1){
                        break;
                    }
                }
            }
            if (checker >= 4){
                return true;
            }
        }
    }
    return false;
}

bool Board::diagonalConnect4() const {
    int upright[2];
    int upLeft[2];
    upright[0] = 1;
    upright[1] = 1;
    upLeft[0] = 1;
    upLeft[1] = -1;

    for(int i(0); i < 3; ++i){
        for(int j(0); j < 4; ++j){
            if(gameBoard[i][j] != 0 && gameBoard[i][j] == gameBoard[i + upright[0]][j + upright[1]]
            == gameBoard[i + 2 * upright[0]][j + 2 * upright[1]] ==
            gameBoard[i + 3 * upright[0]][j + 3 * upright[1]]){
                return true;
            }
        }
    }
    for(int i(0); i < 3; ++i){
        for(int j(0); j < 4; ++j){
            if(gameBoard[i][j] != 0 && gameBoard[i][j] == gameBoard[i + upLeft[0]][j + upLeft[1]]
               == gameBoard[i + 2 * upLeft[0]][j + 2 * upLeft[1]] ==
               gameBoard[i + 3 * upLeft[0]][j + 3 * upLeft[1]]){
                return true;
            }
        }
    }
    return false;
}

bool Board::regret1() {
    int col = history.back();
    if(col > 7){
        std::cout <<"Out of range!\n";
        return false;
    }
    --col;
    for(int i(0); i < ROW; ++i){
        if(gameBoard[i][col] != 0){
            gameBoard[i][col] = 0;
            history.pop_back();
            return true;
        }
    }
    return false;
}

void Board:: process(std::string playerNo1, std::string playerNo2){
    while(!this -> isFull()){
        if(player1 == true){
            std::string tmp("");
            std::cout <<"Which column do " + playerNo1 + " want to put the checker: ";
            std::cin >> tmp;
            if(std::isdigit(tmp[0])){
                bool fit = this ->putChecker(stoi(tmp));
                while(!fit){
                    std::cout <<"Which column do " + playerNo1 + " want to put the checker: ";
                    std::cin >> tmp;
                    fit = this ->putChecker(stoi(tmp));
                }
            }else if(tmp == "store"){
                this ->storeGame(playerNo1,playerNo2);
                std::cout<<"Game stored as " + playerNo1 + "_" + playerNo2 + ".txt\n";
                return;
            }
            if(this -> win()){
                std::cout << playerNo1 + " won!!!";
                this -> getBoard();
                return;
            }
        } else {
            std::string tmp("");
            std::cout <<"Which column do " + playerNo2 + " want to put the checker: ";
            std::cin >> tmp;
            if(std::isdigit(tmp[0])){
                bool fit = this ->putChecker(stoi(tmp));
                while(!fit){
                    std::cout <<"Which column do " + playerNo2 + " want to put the checker: ";
                    std::cin >> tmp;
                    fit = this ->putChecker(stoi(tmp));
                }
            }else if(tmp == "store"){
                this ->storeGame(playerNo1,playerNo2);
                std::cout<<"Game stored as " + playerNo1 + "_" + playerNo2 + ".txt\n";
                return;
            }
            if(this -> win()){
                std::cout << playerNo2 + " won!!!";
                this -> getBoard();
                return;
            }
        }
        this -> getBoard();
    }
    std::cout << "It's a draw.";
}

void Board::startGame() {
    std::cout << "Hi let's start a game of connect4\n";
    std::cout << "What is the name for player 1: ";
    std::string playerNo1;
    std::cin >> playerNo1;

    std::cout << "What is the name for player 2: ";
    std::string playerNo2;
    std::cin >> playerNo2;

    std::string answer;
    std::cout << "Do you want to load a existing game ?\nInput y for Yes and n for No: ";
    std::cin >> answer;

    if(answer == "y"){
        std::cout << "What is the file you want to upload? ";
        std::string fileName;
        std::cin >> fileName;
        this ->loadGame(fileName);
    }

    std::cout <<"Let's start!\n";

    this -> process(playerNo1, playerNo2);

    return;
}

void Board::storeGame(std::string player1Name, std::string player2Name) {
    std::ofstream savedGame(player1Name + " " + player2Name + ".txt");
    for(int i(0); i < ROW; ++i){
        for(int j(0); j < COL; ++j){
            savedGame << gameBoard[i][j];
            savedGame << "_";
        }
        savedGame << "\n";
    }
    savedGame.close();
}
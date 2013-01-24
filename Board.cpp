#include "Board.h"
#include <assert.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

Board::Board() {
    initBoard();
}

Board::Board(const std::string &path) {
    initBoard();
    std::ifstream file(path.c_str());
    if (file.is_open()) {
        std::string line;
        for (int i = HEIGHT - 1; i >= 0; i--) {
            if (file.good()) {
                getline(file, line);
                addLine(line, i);
            } else {
                file.close();
                return;
            }
        }
        initRowCount();
    }
}

/*Board::Board(const Board &board) {
    
}*/

Board::~Board() {

}

int Board::getScore() {
    srand((unsigned)time(0)+(unsigned)getpid());
    return rand() % 10 + 1;
}

void Board::displayBoard() {
    for (int y = HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%d ", getPosition(x,y));
        }
        printf("\n");
    }
}


void Board::initBoard() {
    score = 0;
    for (int x = 0; x < WIDTH; x++) {
        rowCount[x] = 0;
        for(int y = 0; y < HEIGHT; y++) {
            board[x][y] = OPEN;
        }
    }
}

void Board::initRowCount() {
    for (int x = 0; x < WIDTH; x++) {
        for(int y = 0; y < HEIGHT; y++) {
            if (board[x][y]) rowCount[x]++;
        }
    }
}

void Board::addLine(const std::string &line, int row) {
    assert(line.length() >= WIDTH * 2);
    for (int i = 0; i < WIDTH; i++) {
        board[i][row] = (player)(line[2*i] - '0');
    } 
}

player Board::getPosition(int x, int y) const {
    assert(x >= 0);
    assert(x < WIDTH);
    assert(y >= 0);
    assert(y < HEIGHT);
    return board[x][y];
}

bool Board::playAt(int x, player p1) {
    if (!canPlay(x))
        return false;
    board[x][rowCount[x]] = p1;
    rowCount[x]++;
    return true;
}

bool Board::canPlay(int x) const {
    return rowCount[x] < HEIGHT;	
}

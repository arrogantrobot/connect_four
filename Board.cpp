#include "Board.h"
#include <assert.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

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

void Board::initBoard() {
    score = 0;
    lastMove = -1;
    for (int x = 0; x < WIDTH; x++) {
        rowCount[x] = 0;
        for(int y = 0; y < HEIGHT; y++) {
            board[x][y] = OPEN;
        }
    }
}

int Board::getScore(player p) {
    int score = 0;
    player who;
    if (fourInARow(who))
        score = (p == who) ? INT_MIN : score = INT_MAX;
    
    return score;
}

bool Board::fourInARow(player &p) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (board[x][y]) {
                for (int direction = 0; direction < 8; direction++) {
                    if(fourInThisRow(x, y, direction) == 4) {
                        p = board[x][y];
                        printf("Found 4 in a row, from player: %d\n", p);
                        displayBoard();
                        return true;
                    }
                }
            }
        }
    }
}

int Board::fourInThisRow(int x, int y, int direction) {
    int answer = 1;
    switch (direction) {
        case 0: if (x < WIDTH - 1) {
                    if (board[x + 1][y] == board[x][y]) {
                        answer += fourInThisRow(x + 1, y, direction);
                    }
                }
                break;

        case 1: if (x < WIDTH - 1 && y < HEIGHT - 1) {
                    if (board[x + 1][y + 1] == board[x][y]) {
                        answer += fourInThisRow(x + 1, y + 1, direction);
                    }
                }
                break;

        case 2: if (y < HEIGHT - 1) {
                    if (board[x][y + 1] == board[x][y]) {
                        answer += fourInThisRow(x, y + 1, direction);
                    }
                }
                break;

        case 3: if (x > 0 && y < HEIGHT - 1) {
                    if (board[x - 1][y + 1] == board[x][y]) {
                        answer += fourInThisRow(x - 1, y + 1, direction);
                    }
                }
                break;

        case 4: if (x > 0) {
                    if (board[x - 1][y] == board[x][y]) {
                        answer += fourInThisRow(x - 1, y, direction);
                    }
                }
                break;

        case 5: if (x > 0 && y > 0) {
                    if (board[x - 1][y - 1] == board[x][y]) {
                        answer += fourInThisRow(x - 1, y - 1, direction);
                    }
                }
                break;

        case 6: if (y > 0) {
                    if (board[x][y - 1] == board[x][y]) {
                        answer += fourInThisRow(x, y - 1, direction);
                    }
                }
                break;

        case 7: if (x < WIDTH - 1 && y > 0) {
                    if (board[x][y - 1] == board[x][y]) {
                        answer += fourInThisRow(x, y - 1, direction);
                    }
                }
                break;
    }
    return answer;
}

void Board::displayBoard() {
    printf("\n");
    for (int y = HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%d ", getPosition(x,y));
        }
        printf("\n");
    }
    printf("last move: %d\n", lastMove);
    displayRowCount();
    printf("\n");
}

void Board::displayRowCount() {
    for (int i = 0; i < WIDTH; i++) {
        printf("row: %d   pieces: %d\n", i, rowCount[i]);
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
    lastMove = x;
    return true;
}

void Board::unPlayAt(int x) {
    rowCount[x]--;
    board[x][rowCount[x]] = OPEN;
    lastMove = -1;
}

int Board::getLastMove() const {
    return lastMove;
}

bool Board::canPlay(int x) const {
    return rowCount[x] < HEIGHT;	
}

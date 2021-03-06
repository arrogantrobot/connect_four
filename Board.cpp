#include "Board.h"
#include <assert.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

Board::Board(): score(0), lastMove(-1), fiar(OPEN), fiarSet(false),
        fourInARowFound(false) {
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

Board::Board(const Board &_board) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            board[x][y] = _board.board[x][y];
            positionValues[x][y] = _board.positionValues[x][y];
        }
    }
    for (int i = 0; i < WIDTH; i++) {
        rowCount[i] = _board.rowCount[i];
    }
    playCount = _board.playCount;
    score = _board.score;
    lastMove = _board.lastMove;
    fourInARowFound = _board.fourInARowFound;
    fiarSet = _board.fiarSet;
    fiar = _board.fiar;
}

Board::~Board() {

}

bool Board::operator==(const Board& rhs) const {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (board[x][y] != rhs.board[x][y]) return false;
        }
    }
    return true;
}

void Board::initBoard() {
    score = 0;
    lastMove = -1;
    fiar = OPEN;
    fourInARowFound = false;
    fiarSet = false;
    populatePositionValues();

    for (int x = 0; x < WIDTH; x++) {
        rowCount[x] = 0;
        for(int y = 0; y < HEIGHT; y++) {
            board[x][y] = OPEN;
        }
    }
}

int Board::getScore(const player p) const {
    int score = 0;
    if (boardFull()) return 0;
    player who = OPEN;
    score += getPositionalScore(p);
    if (fourInARow())
        score = INT_MAX;
    return score;
}

bool Board::fourInARow() const{
    //before we search, check to see if this board has been searched
    if (fiarSet) {
        return fourInARowFound;
    }
    //search for four in a row
    for (int x = 0; x < WIDTH; x++) {
        if (rowCount[x]) {
            for (int y = 0; y < HEIGHT; y++) {
                if (rowCount[x] > y && board[x][y]) {
                    for (int direction = 0; direction < 8; direction++) {
                        if(fourInThisRow(x, y, direction) == 4) {
                            fiar = board[x][y];
                            fourInARowFound = true;
                            fiarSet = true;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

/**
 *  Search for four in a row in direction 
 *
 *  Direction is zero at 0 degrees:
 *
 * +-----+
 * |3|2|1|
 * |-+-+-|    
 * |4|X|0| 
 * |-+-+-|
 * |5|6|7|
 * +-----+
 */
int Board::fourInThisRow(int x, int y, int direction) const {
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

void Board::displayBoard() const {
    //printf("\n");
    for (int y = HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIDTH; x++) {
            char out;
            switch(getPosition(x,y)) {
            case OPEN: out = '.';
                       break;
            case PLAYER_ONE: out = 'X';
                       break;
            case PLAYER_TWO: out = 'O';
                       break;
            }
            printf("%c ", out);
        }
        printf("\n");
    }
    //printf("last move: %d\n", lastMove);
    //displayRowCount();
    //printf("\n");
}

void Board::displayRowCount() const {
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
    if (x < 0 || x >= WIDTH) 
        return false;
    if (!canPlay(x))
        return false;
    board[x][rowCount[x]] = p1;
    rowCount[x]++;
    playCount++;
    lastMove = x;
    return true;
}

void Board::unPlayAt(int x) {
    if (rowCount[x] > 0) {
        rowCount[x]--;
        playCount--;
        board[x][rowCount[x]] = OPEN;
        lastMove = -1;
        fiar = OPEN;
        fiarSet = false;
        fourInARowFound = false;
    }
}

int Board::getLastMove() const {
    return lastMove;
}

bool Board::canPlay(int x) const {
    return (x >= 0 && x < WIDTH) && rowCount[x] < HEIGHT;
}

bool Board::boardFull() const {
   return playCount >= WIDTH * HEIGHT;
}

int Board::getPositionalScore(player p) const {
    int answer = 0;
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (board[x][y] == p)
                answer += positionValues[x][y];
        }
    }
    return answer;
}

void Board::populatePositionValues() {
    int xInc = 1, yInc = 1;
    int xMid = WIDTH / 2;
    int yMid = HEIGHT / 2;
    int xVal = 0, yVal = 0;
    for (int x = 0; x < WIDTH; x++) {
        if (x > xMid) xInc = -1;
        xVal = xVal + xInc ;
        for (int y = 0; y < HEIGHT; y++) {
            positionValues[x][y] = xVal;
        }
    }
    for (int y = 0; y < HEIGHT; y++) {
        if (y > yMid) yInc = -1;
        yVal = yVal + yInc ;
        for (int x = 0; x < WIDTH; x++) {
            positionValues[x][y] += yVal;
        }
    }
}

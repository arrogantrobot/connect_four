#ifndef __BOARD_H__
#define __BOARD_H__

#include <string>

#define HEIGHT 6
#define WIDTH 7

typedef enum {
    OPEN,
    PLAYER_ONE,
    PLAYER_TWO
} player;

class Board {
    public:
        Board();
        Board(const std::string &path);
        ~Board();
        player getPosition(int x, int y) const;
        bool playAt(int x, player p1);
        bool canPlay(int x);
        int getScore(player p);
        int getLastMove() const;
        void unPlayAt(int x);
        void displayBoard();
        void displayRowCount();
        bool fourInARow(player &p);
        bool operator==(const Board& rhs) const;

    private:
        void initBoard();
        void initRowCount();
        void addLine(const std::string &line, int row);
        int fourInThisRow(int x, int y, int direction);
        void populatePositionValues();
        int getPositionalScore(player p) const;

        player board[WIDTH][HEIGHT];
        int score;
        int rowCount[WIDTH];
        int lastMove;
        int positionValues[WIDTH][HEIGHT];
        bool fourInARowFound, fiarSet;
        player fiar;
};

#endif

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
        int getScore(const player p) const;
        int getLastMove() const;
        void unPlayAt(int x);
        void displayBoard();
        void displayRowCount();
        bool fourInARow(player &p) const;
        bool operator==(const Board& rhs) const;

    private:
        void initBoard();
        void initRowCount();
        void addLine(const std::string &line, int row);
        int fourInThisRow(int x, int y, int direction) const;
        void populatePositionValues();
        int getPositionalScore(player p) const;

        player board[WIDTH][HEIGHT];
        int rowCount[WIDTH];
        int positionValues[WIDTH][HEIGHT];

        int score;
        int lastMove;
        mutable bool fourInARowFound;
        mutable bool fiarSet;
        mutable player fiar;
};

#endif

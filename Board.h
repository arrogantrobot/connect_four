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
        Board(const Board &board);
        Board(const std::string &path);
        ~Board();

        void unPlayAt(int x);
        void displayBoard() const;
        void displayRowCount() const;

        bool playAt(int x, player p1);
        bool canPlay(int x) const;
        bool fourInARow() const;
        bool boardFull() const;
        bool operator==(const Board& rhs) const;

        int getScore(const player p) const;
        int getLastMove() const;

        player getPosition(int x, int y) const;

    protected:
        void initBoard();
        void initRowCount();
        void addLine(const std::string &line, int row);
        int fourInThisRow(int x, int y, int direction) const;
        void populatePositionValues();
        int getPositionalScore(player p) const;

        player board[WIDTH][HEIGHT];
        int rowCount[WIDTH];
        int positionValues[WIDTH][HEIGHT];

        int playCount;
        int score;
        int lastMove;
        mutable bool fourInARowFound;
        mutable bool fiarSet;
        mutable player fiar;
};

#endif

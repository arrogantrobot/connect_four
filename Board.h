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

    private:
        void initBoard();
        void addLine(const std::string &line, int row);
        player board[WIDTH][HEIGHT];
        int rowCount[WIDTH];
        bool canPlay(int x) const;
};

#endif

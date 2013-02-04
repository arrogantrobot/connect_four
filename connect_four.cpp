#include "Board.h"
#include "MiniMaxTree.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    std::string path = argv[1];
    Board b(path);
    MiniMaxTree miniMaxTree(b, PLAYER_ONE, 10);
    int move = miniMaxTree.getBestMoveAB();
    b.playAt(move, PLAYER_ONE);
    b.displayBoard();
    return 0;
}

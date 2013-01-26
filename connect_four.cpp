#include "Board.h"
#include "MiniMaxTree.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    std::string path = argv[1];
    Board b(path);
    b.displayBoard();
    MiniMaxTree miniMaxTree(b, 6);
    int move = miniMaxTree.getBestMove();
    b.playAt(move, PLAYER_ONE);
    printf("\n\n");
    b.displayBoard();
    return 0;
}

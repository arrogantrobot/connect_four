#include "Board.h"
#include "MiniMaxTree.h"
#include <stdio.h>

void displayBoard(const Board &b) {
    for (int y = HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%d ", b.getPosition(x,y));
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    std::string path = argv[1];
    Board b(path);
    displayBoard(b);
    MiniMaxTree miniMaxTree(b, 2);
    int move = miniMaxTree.getBestMove();
    b.playAt(move, PLAYER_ONE);
    printf("\n\n");
    b.displayBoard();
    return 0;
}

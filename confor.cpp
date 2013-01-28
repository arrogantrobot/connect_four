#include <stdio.h>
#include "MiniMaxTree.h"
#include "Board.h"

int getPlayerMove() {
    printf("Enter the column you wish to move at: ");
    int move = -1;
    int rc = 0;
    rc = fscanf(stdin, "%d", &move);
    return move;
}
int main(int argc, char * argv[]) {
    printf("\nConnect Four\n");
    printf("============\n");
    printf("\n");
    Board board;
    //board.displayBoard();
    bool fiar = false;
    int playCount = 0;
    while (1) {
        printf("strategizing...\n");
        MiniMaxTree miniMaxTree(board,(playCount > 35) ? 42 - playCount : 7);
        int move = miniMaxTree.getBestMove();
        printf("The computer has moved at column: %d\n\n", move);
        board.playAt(move, PLAYER_ONE);
        playCount++;
        printf("0 1 2 3 4 5 6\n");
        board.displayBoard();
        printf("0 1 2 3 4 5 6\n");
        player p = OPEN;
        if (board.fourInARow(p)) {
            printf("The computer has won!\n");
            break;
        }
        move = getPlayerMove();
        board.playAt(move, PLAYER_TWO);
        playCount++;
        if (board.fourInARow(p)) {
            printf("You have won!\n");
            break;
        }
    }
    board.displayBoard();

    return 0;
}


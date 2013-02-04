#include <stdio.h>
#include "MiniMaxTree.h"
#include "Board.h"

void showBoard(Board &board) {

    printf("0 1 2 3 4 5 6\n");
    board.displayBoard();
    printf("0 1 2 3 4 5 6\n");

}

bool playerMoves(Board &board, player human, int &playCount) {
    printf("Enter the column you wish to move at: ");
    int move = -1;
    int rc = 0;
    rc = fscanf(stdin, "%d", &move);
    board.playAt(move, human);
    playCount++;
    if (board.fourInARow()) {
        printf("You have won!\n");
        return true;
    }
    return false;
}

bool computerMoves(Board &board, player computer, int &playCount) {
    printf("strategizing...\n");
    MiniMaxTree miniMaxTree(board, computer,
            (playCount > 35) ? 42 - playCount : 8);
    int move = miniMaxTree.getBestMoveAB();
    printf("The computer has moved at column: %d\n\n", move);
    board.playAt(move, computer);
    playCount++;
    if (board.fourInARow()) {
        printf("The computer has won!\n");
        return true;
    }
    return false;
}

int main(int argc, char * argv[]) {
    bool compFirst = argc == 1;
    printf("\nConnect Four\n");
    printf("============\n");
    printf("\n");
    bool fiar = false;
    bool over = false;
    int playCount = 0;
    Board board;
    player computer = compFirst ? PLAYER_ONE : PLAYER_TWO;
    player human = compFirst ? PLAYER_TWO : PLAYER_ONE;
    showBoard(board);

    while (1) {
        over = compFirst ? computerMoves(board, computer, playCount)
            : playerMoves(board, human, playCount);
        if (over) break;
        if (compFirst) showBoard(board);
        over = compFirst ? playerMoves(board, human, playCount)
            : computerMoves(board, computer, playCount);
        if (over) break;
        if (!compFirst) showBoard(board);
    }

    board.displayBoard();

    return 0;
}


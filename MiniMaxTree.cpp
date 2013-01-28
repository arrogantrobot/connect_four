#include <stdio.h>
#include "MiniMaxTree.h"

MiniMaxTree::MiniMaxTree(const Board &_board, int _ply) {
    ply = _ply;
    nodesVisited = 0;
    rootBoard = _board;
}

MiniMaxTree::~MiniMaxTree() {

}

int MiniMaxTree::getBestMove() {
    Board board = rootBoard;
    BestMove bm = getBestMoveScore(board, PLAYER_TWO, ply);
    //printf("nodesVisited: %d\n", nodesVisited);
    //printf("score: %d\n", bm.score);
    return bm.columnPlayed;
}

BestMove MiniMaxTree::getBestMoveScore(Board board, player p, int currentPly) {
    BestMove bestMove;
    bestMove.score = (p == PLAYER_TWO) ? INT_MIN : INT_MAX;
    nodesVisited++;
    player x;
    if (currentPly == 0 || board.fourInARow(x)) {
        bestMove.score = board.getScore(p);
        //board.displayBoard();
        if (p == PLAYER_TWO)
            bestMove.score = bestMove.score * -1;
        bestMove.columnPlayed = board.getLastMove();
        return bestMove;
    }
    player next = (p == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
    for (int i = 0; i < WIDTH; i++) {
        if (board.canPlay(i)) {

            board.playAt(i, next);
            BestMove local = getBestMoveScore(board, next, currentPly - 1);
            local.columnPlayed = i;
            board.unPlayAt(i);

            if (next == PLAYER_ONE) {
                if (local.score > bestMove.score) {
                    //printf("best move p: %d  col: %d  score: %d\n",next, local.columnPlayed, local.score);
                    bestMove = local;
                }
            } else {
                if (local.score < bestMove.score) {
                    //printf("best move p: %d  col: %d  score: %d\n", next, local.columnPlayed, local.score);
                    bestMove = local;
                }
            }
        }
    }
    return bestMove; 
}

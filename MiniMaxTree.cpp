#include <stdio.h>
#include "MiniMaxTree.h"

MiniMaxTree::MiniMaxTree(const Board &_board, player p, int _ply) {
    computer = p;
    miniMaxSeed = (p == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
    ply = _ply;
    nodesVisited = 0;
    rootBoard = _board;
}

MiniMaxTree::~MiniMaxTree() {

}

int MiniMaxTree::getBestMove() {
    BestMove bm = getBestMoveScore(rootBoard, miniMaxSeed, ply);
    return bm.columnPlayed;
}

BestMove MiniMaxTree::getBestMoveScore(Board board, player p, int currentPly) {
    BestMove bestMove;
    bestMove.score = (p != computer) ? INT_MIN : INT_MAX;
    nodesVisited++;
    player x;
    if (currentPly == 0 || board.boardFull() || board.fourInARow(x)) {
        bestMove.score = board.getScore(p);
        if (p == miniMaxSeed)
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

            if (next == computer) {
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

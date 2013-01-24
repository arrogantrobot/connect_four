#include "MiniMaxTree.h"

MiniMaxTree::MiniMaxTree(const Board &_board, int _ply) {
    ply = _ply;
    rootBoard = _board;
}

MiniMaxTree::~MiniMaxTree() {

}

int MiniMaxTree::getBestMove() {
    Board board = rootBoard;
    BestMove bm = getBestMoveScore(&board, PLAYER_ONE, ply);
    return bm.columnPlayed;
}

BestMove MiniMaxTree::getBestMoveScore(Board *board, player p, int currentPly) {
    BestMove bestMove;
    if (currentPly == 0) {
        bestMove.score = board->getScore(p);
        return bestMove;
    }
    player next = (p == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
    for (int i = 0; i < WIDTH; i++) {
        if (board->canPlay(i)) {
            board->playAt(i, p);
            BestMove local = getBestMoveScore(board, next, currentPly - 1);
            if (local.score > bestMove.score) {
                bestMove = local;
                bestMove.columnPlayed = i;
            }
        }
    }
    return bestMove; 
}

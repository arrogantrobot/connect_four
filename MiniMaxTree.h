#ifndef __MINI_MAX_TREE_H__
#define __MINI_MAX_TREE_H__

#include <limits.h>
#include "Board.h"

struct BestMove {
    BestMove(): columnPlayed(-1),score(0) {}
    int columnPlayed;
    int score;
};

static int max_score = INT_MAX;
static int min_score = INT_MIN + 1;

class MiniMaxTree {
    public:
        MiniMaxTree(const Board &_board, player p, int ply);
        ~MiniMaxTree();
        int getBestMove();
        int getBestMoveAB();
        BestMove getBestMoveScore(Board board, player p, int ply);
        BestMove getBestMoveScoreAB(Board board, player p, player o, int ply, int alpha, int beta);
    protected:
        int nodesVisited;
        int ply;
        Board rootBoard;
        player computer, miniMaxSeed;
};

#endif

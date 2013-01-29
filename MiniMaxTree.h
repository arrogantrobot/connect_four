#ifndef __MINI_MAX_TREE_H__
#define __MINI_MAX_TREE_H__

#include <limits.h>
#include "Board.h"

struct BestMove {
    BestMove(): columnPlayed(-1),score(0) {}
    int columnPlayed;
    int score;
};

class MiniMaxTree {
    public:
        MiniMaxTree(const Board &_board, player p, int ply);
        ~MiniMaxTree();
        int getBestMove();
        BestMove getBestMoveScore(Board board, player p, int ply);
    private:
        int nodesVisited;
        int ply;
        Board rootBoard;
        player computer, miniMaxSeed;
};
#endif

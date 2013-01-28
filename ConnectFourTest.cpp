#include "gtest/gtest.h"
#include "MiniMaxTree.h"

TEST(ConnectFourTest, BoardSetup) {
    Board board;
    player p1 = PLAYER_ONE;
    player p2 = PLAYER_TWO;

    EXPECT_EQ(0, board.getScore(p1));
    EXPECT_EQ(0, board.getScore(p2));

    EXPECT_EQ(-1, board.getLastMove());
    EXPECT_FALSE(board.fourInARow(p1));
}

TEST(ConnectFourTest, BoardSetupFromFiles) {
    std::string path = "board_new.txt";
    Board board(path);
    player p = OPEN;
    EXPECT_FALSE(board.fourInARow(p));
    Board boardNew;
    EXPECT_EQ(board, boardNew);
}   

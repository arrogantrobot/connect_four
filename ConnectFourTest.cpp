#include "gtest/gtest.h"
#include "MiniMaxTree.h"

class TestBoard : public Board {
    public:
        void getBoard(int b[WIDTH][HEIGHT]) {
            for (int x = 0; x < WIDTH; x++) {
                for (int y = 0; y < HEIGHT; y++) {
                    b[x][y] = board[x][y];
                }
            }
        };
};

TEST(ConnectFourTest, BoardSetup) {
    Board board;
    player p1 = PLAYER_ONE;
    player p2 = PLAYER_TWO;

    EXPECT_EQ(0, board.getScore(p1));
    EXPECT_EQ(0, board.getScore(p2));

    EXPECT_EQ(-1, board.getLastMove());
    EXPECT_FALSE(board.fourInARow());
}

TEST(ConnectFourTest, BoardSetupFromFiles) {
    std::string path = "board_new.txt";
    Board board(path);
    EXPECT_FALSE(board.fourInARow());
    Board boardNew;
    EXPECT_EQ(board, boardNew);
}   

TEST(ConnectFourTest, Moves) {
    TestBoard board;
    board.playAt(0, PLAYER_ONE);
    int b[WIDTH][HEIGHT];
    board.getBoard(b);
    EXPECT_EQ(PLAYER_ONE, b[0][0]);

    board.unPlayAt(0);
    board.getBoard(b);
    EXPECT_EQ(OPEN, b[0][0]);
}

TEST(ConnectFourTest, EvaluateMoves) {
    TestBoard board;
    board.playAt(0, PLAYER_ONE);
    board.playAt(1, PLAYER_ONE);
    board.playAt(2, PLAYER_ONE);
    board.playAt(3, PLAYER_ONE);
    int b[WIDTH][HEIGHT];
    board.getBoard(b);
    EXPECT_TRUE(board.fourInARow());
}

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

    EXPECT_FALSE(board.playAt(-1, PLAYER_ONE));
    EXPECT_FALSE(board.canPlay(-1));

    TestBoard board2;
    board2.playAt(0, PLAYER_ONE);
    board2.playAt(0, PLAYER_ONE);
    board2.playAt(0, PLAYER_ONE);
    board2.playAt(0, PLAYER_ONE);
    board2.playAt(0, PLAYER_ONE);
    board2.playAt(0, PLAYER_ONE);

    EXPECT_FALSE(board2.playAt(0, PLAYER_ONE));
}

TEST(ConnectFourTest, EvaluateMoves) {
    TestBoard board;
    EXPECT_FALSE(board.fourInARow());

    EXPECT_TRUE(board.playAt(0, PLAYER_ONE));
    EXPECT_FALSE(board.fourInARow());

    EXPECT_TRUE(board.playAt(1, PLAYER_ONE));
    EXPECT_FALSE(board.fourInARow());

    EXPECT_TRUE(board.playAt(2, PLAYER_ONE));
    EXPECT_FALSE(board.fourInARow());

    EXPECT_TRUE(board.playAt(3, PLAYER_ONE));

    int b[WIDTH][HEIGHT];
    board.getBoard(b);
    EXPECT_TRUE(board.fourInARow());
}

TEST(ConnectFourTest, MiniMaxTreeTests) {
    Board board;
    MiniMaxTree mmt(board, PLAYER_ONE, 1);
    int move = mmt.getBestMove();
    EXPECT_EQ(move, 3);
    printf("move = %d\n", move);
}

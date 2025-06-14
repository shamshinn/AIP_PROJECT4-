#include "gtest/gtest.h"
#include "GameLogic.h"

TEST(GameLogicTest, InitialState) {
    GameLogic game(400, 400);

    EXPECT_EQ(game.GetSnake().size(), 1);
    EXPECT_FALSE(game.IsGameOver());
    EXPECT_EQ(game.GetScore(), 0);

    auto fruitPos = game.GetFruitPosition();
    EXPECT_GE(fruitPos.x, 0);
    EXPECT_GE(fruitPos.y, 0);
    EXPECT_LT(fruitPos.x, 400);
    EXPECT_LT(fruitPos.y, 400);
}

TEST(GameLogicTest, SnakeMovement) {
    GameLogic game(400, 400);
    auto initialPos = game.GetSnake().front();

    game.MoveSnake();
    auto newPos = game.GetSnake().front();
    EXPECT_EQ(newPos.x, initialPos.x + game.GetBlockSize());
    EXPECT_EQ(newPos.y, initialPos.y);

    game.ChangeDirection(0, 1);
    game.MoveSnake();
    newPos = game.GetSnake().front();
    EXPECT_EQ(newPos.x, initialPos.x + game.GetBlockSize());
    EXPECT_EQ(newPos.y, initialPos.y + game.GetBlockSize());
}

TEST(GameLogicTest, SnakeGrowth) {
    GameLogic game(400, 400);
    size_t initialSize = game.GetSnake().size();

    GameLogic::Point head = game.GetSnake().front();
    game.SetFruitPosition(GameLogic::Point{
        head.x + game.GetBlockSize(),
        head.y
        });

    game.MoveSnake();

    EXPECT_EQ(game.GetSnake().size(), initialSize + 1);
    EXPECT_EQ(game.GetScore(), 1);
}

TEST(GameLogicTest, CollisionDetection) {
    GameLogic game(400, 400);

    game.ChangeDirection(-1, 0);
    for (int i = 0; i < 100; i++) {
        game.MoveSnake();
        if (game.IsGameOver()) break;
    }

    EXPECT_TRUE(game.IsGameOver());
}

TEST(GameLogicTest, SelfCollision) {
    GameLogic game(400, 400);

    game.SetFruitPosition(GameLogic::Point{ 120, 100 });
    game.MoveSnake();
    game.SetFruitPosition(GameLogic::Point{ 140, 100 });
    game.MoveSnake();
    game.SetFruitPosition(GameLogic::Point{ 160, 100 });
    game.MoveSnake();

    game.ChangeDirection(0, 1);
    game.MoveSnake();
    game.ChangeDirection(-1, 0);
    game.MoveSnake();
    game.ChangeDirection(0, -1);
    game.MoveSnake();

    EXPECT_TRUE(game.IsGameOver());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
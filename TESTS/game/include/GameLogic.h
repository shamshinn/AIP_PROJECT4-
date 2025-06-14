#pragma once
#include <vector>
#include <utility>

class GameLogic {
public:
    struct Point {
        int x, y;
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    GameLogic(int width, int height, int blockSize = 20);

    void PlaceFruit();
    void MoveSnake();
    void GrowSnake();
    void ChangeDirection(int newMoveX, int newMoveY);

    // Геттеры
    int GetScore() const { return fruitCount; }
    Point GetFruitPosition() const { return fruitPosition; }
    const std::vector<Point>& GetSnake() const { return snake; }
    bool IsGameOver() const { return gameOver; }
    int GetBlockSize() const { return blockSize; }

    // Сеттер
    void SetFruitPosition(Point newPosition);

private:
    bool CheckSelfCollision(const Point& newHead) const;

    std::vector<Point> snake;
    Point fruitPosition;
    int moveX, moveY;
    int blockSize;
    int fieldWidth, fieldHeight;
    int fruitCount = 0;
    bool gameOver = false;
};
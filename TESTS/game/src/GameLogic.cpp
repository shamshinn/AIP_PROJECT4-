#include "GameLogic.h"
#include <cstdlib>
#include <algorithm>

GameLogic::GameLogic(int width, int height, int blockSize)
    : fieldWidth(width), fieldHeight(height), blockSize(blockSize) {
    snake.push_back({ width / 2, height / 2 });
    moveX = 1;
    moveY = 0;
    PlaceFruit();
}

bool GameLogic::CheckSelfCollision(const Point& newHead) const {
    // Проверяем все сегменты, кроме головы (begin()+1)
    return std::find(snake.begin() + 1, snake.end(), newHead) != snake.end();
}

void GameLogic::SetFruitPosition(Point newPosition) {
    if (newPosition.x >= 0 && newPosition.y >= 0 &&
        newPosition.x < fieldWidth && newPosition.y < fieldHeight) {
        fruitPosition = newPosition;
    }
}

void GameLogic::PlaceFruit() {
    do {
        fruitPosition = {
            (rand() % (fieldWidth / blockSize)) * blockSize,
            (rand() % (fieldHeight / blockSize)) * blockSize
        };
    } while (std::find(snake.begin(), snake.end(), fruitPosition) != snake.end());
}

void GameLogic::MoveSnake() {
    Point newHead = { snake.front().x + moveX * blockSize,
                    snake.front().y + moveY * blockSize };

    // Проверка столкновений
    if (newHead.x < 0 || newHead.y < 0 ||
        newHead.x >= fieldWidth || newHead.y >= fieldHeight ||
        CheckSelfCollision(newHead)) {
        gameOver = true;
        return;
    }

    snake.insert(snake.begin(), newHead);

    if (newHead == fruitPosition) {
        fruitCount++;
        PlaceFruit();
    }
    else {
        snake.pop_back();
    }
}

void GameLogic::GrowSnake() {
    Point newHead = { snake.front().x + moveX * blockSize,
                    snake.front().y + moveY * blockSize };
    snake.insert(snake.begin(), newHead);
}

void GameLogic::ChangeDirection(int newMoveX, int newMoveY) {
    if (moveX != -newMoveX || moveY != -newMoveY) {
        moveX = newMoveX;
        moveY = newMoveY;
    }
}
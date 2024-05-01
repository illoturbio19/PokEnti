#pragma once
#include <iostream>
#include <Windows.h>
enum class Movement { UP, DOWN, LEFT, RIGHT, INVALID };
class Ash {
private:
    int x; // X position of Ash
    int y; // Y position of Ash

public:
    Ash(int initialX, int initialY);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    int getX();
    int getY();
};

#include "Ash.h"


Ash::Ash(int initialX, int initialY) : x(initialX), y(initialY) {}

void Ash::moveUp() {
    y--;
}

void Ash::moveDown() {
    y++;
}

void Ash::moveLeft() {
    x--;
}

void Ash::moveRight() {
    x++;
}

int Ash::getX() {
    return x;
}

int Ash::getY() {
    return y;
}
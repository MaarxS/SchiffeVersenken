#pragma once
#include "Cell.hpp"

class Field {
    Cell field[10][10];
    bool isShipAdjacent(int x, int y);
    bool isCompletelySunken(int x, int y);
    void markSunkenShip(int x, int y);

    public:
    bool placeShip(int startx, int starty, int endx, int endy);
    void shoot(int x, int y);
    void printField(bool isOwnField);
};
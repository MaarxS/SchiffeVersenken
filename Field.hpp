#pragma once
#include "Cell.hpp"

class Field {
    Cell field[10][10];

    public:
    Field();
    void printField(bool isOwnField);
    bool placeShip(int startx, int starty, int endx, int endy);
};
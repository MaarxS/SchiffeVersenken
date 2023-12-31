#pragma once
#include "Field.hpp"

class Computer {
    Field field;
    void placeRandomShip(int length);

    public:
    void placeShips();
    Field* getField();
};
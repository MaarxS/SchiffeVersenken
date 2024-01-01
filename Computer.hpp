#pragma once
#include "Field.hpp"

class Computer {
    Field field;
    void placeRandomShip(int length);
    void continueFindingShip(Field &field, int x, int y);

    public:
    void placeShips();
    Field* getField();
    void shoot(Field &enemyField);
};
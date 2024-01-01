#pragma once
#include "Field.hpp"

class Computer {
    void placeRandomShip(Field &field, int length);
    void continueFindingShip(Field &field, int x, int y);

    public:
    void placeShips(Field &field);
    void shoot(Field &enemyField);
};
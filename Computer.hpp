#pragma once
#include "Field.hpp"
#include "CppRandom.hpp"

class Computer {
    Random rand;
    void placeRandomShip(Field &field, int length);
    void continueFindingShip(Field &field, int x, int y);
    bool shootRandomFreeCoordinate(Field &field);
    bool guessOrientation(Field field, int x, int y);

    public:
    void placeShips(Field &field);
    void shoot(Field &enemyField);
};
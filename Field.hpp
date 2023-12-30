#pragma once
#include "Cell.hpp"

class Field {
    Cell field[10][10];

    public:
    void printOwnField();
    void printEnemyField();
};
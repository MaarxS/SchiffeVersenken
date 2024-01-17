#pragma once
#include "Field.hpp"
#include "CppRandom.hpp"
#include <memory>

class Computer {
    std::shared_ptr<Random> rand;
    std::shared_ptr<Field> ownfield;
    std::shared_ptr<Field> enemyfield;
    void placeRandomShip(int length);
    bool continueShootingDirection(int dir, int x, int y);
    void continueFindingShip(int x, int y);
    std::pair<int, int> findDamagedShip();
    bool shootRandomFreeCoordinate();
    bool guessOrientation(int x, int y);

    public:
    Computer(std::shared_ptr<Random> rand, std::shared_ptr<Field> ownfield, std::shared_ptr<Field> enemyfield): rand(rand), ownfield(ownfield), enemyfield(enemyfield) {}
    void placeShips();
    void shoot();
};
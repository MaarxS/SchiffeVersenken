#pragma once
#include "Field.hpp"
#include "CppRandom.hpp"
#include <memory>

class Computer {
    bool hardDifficulty;
    std::shared_ptr<Random> rand;
    std::shared_ptr<Field> ownField;
    std::shared_ptr<Field> enemyField;
    void placeRandomShip(int length);
    bool continueShootingDirection(int dir, int x, int y);
    void continueFindingShip(int x, int y);
    std::pair<int, int> findDamagedShip();
    bool shootRandomFreeCoordinate();
    bool guessOrientation(int x, int y);

    public:
    Computer(std::shared_ptr<Random> rand, std::shared_ptr<Field> ownField, std::shared_ptr<Field> enemyField): rand(rand), ownField(ownField), enemyField(enemyField) {}
    void placeShips();
    void shoot();
    void setHardDifficulty(bool difficulty);
    bool getHardDifficulty();
};

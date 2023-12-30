#pragma once

class Cell {
    bool ship = false;
    bool hit = false;

    public:
    bool isHitShip();
    bool isMissedShot();
    bool isShip();
    void shoot();
    void placeShip();
};

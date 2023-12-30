#pragma once

class Cell {
    bool isShip = false;
    bool isHit = false;

    public:
    bool isSunkenShip();
    bool isMissedShot();
    bool isShip();
    bool shoot();
};

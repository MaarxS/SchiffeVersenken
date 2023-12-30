#pragma once

class Cell {
    bool ship = false;
    bool hit = false;

    public:
    Cell(bool isShip);
    bool isSunkenShip();
    bool isMissedShot();
    bool isShip();
    void shoot();
};

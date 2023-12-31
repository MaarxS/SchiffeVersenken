#pragma once

class Cell {
    bool ship = false;
    bool hit = false;

    public:
    bool isShot();
    bool isShip();
    void shoot();
    void placeShip();
};

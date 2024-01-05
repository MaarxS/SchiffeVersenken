#pragma once

typedef struct {
    bool ship = false;
    bool hit = false;
} Cell;

class Field {
    Cell field[10][10];
    bool isShipAdjacent(int x, int y);
    void shootAroundShip(int x, int y);

    public:
    bool placeShip(int startx, int starty, int endx, int endy);
    void clear();
    bool isClear();
    void shoot(int x, int y);
    void setShip(int x, int y);
    void setShot(int x, int y);
    bool isShip(int x, int y);
    bool isShot(int x, int y);
    bool isCompletelySunken(int x, int y);
    bool isFinished();
    void printField(bool isOwnField);
};
#include "Cell.hpp"

Cell::Cell(bool isShip) {
    ship = isShip;
}

bool Cell::isSunkenShip() {
    return ship && hit;
}

bool Cell::isMissedShot() {
    return !ship && hit;
}

bool Cell::isShip() {
    return ship;
}

void Cell::shoot() {
    hit = true;
}
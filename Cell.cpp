#include "Cell.hpp"

bool Cell::isHitShip() {
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

void Cell::placeShip() {
    ship = true;
}
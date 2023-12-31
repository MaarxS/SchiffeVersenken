#include "Cell.hpp"

bool Cell::isShot() {
    return hit;
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
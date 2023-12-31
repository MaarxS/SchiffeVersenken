#include "Computer.hpp"
#include "Field.hpp"
#include "CppRandom.hpp"

Field* Computer::getField() {
    return &field;
}

void Computer::placeShips() {
    bool success = false;
    while (!success) {
        try {
            placeRandomShip(5);
            placeRandomShip(4);
            placeRandomShip(4);
            placeRandomShip(3);
            placeRandomShip(3);
            placeRandomShip(3);
            placeRandomShip(2);
            placeRandomShip(2);
            placeRandomShip(2);
            placeRandomShip(2);
            success = true;
        } catch (std::logic_error &e) {
            Field newField;
            field = newField;
        }
    }
}

void Computer::placeRandomShip(int length) {
    for (int i = 0; i < 100000; i++) {
        int max = 10 - length;
        int startx = 0;
        int starty;
        int endx;
        int endy;
        if (GetRandomNumberBetween(0, 1)) {
            startx = GetRandomNumberBetween(0, max);
            starty = GetRandomNumberBetween(0, 9);
            endx = startx + length - 1;
            endy = starty;
        } else {
            startx = GetRandomNumberBetween(0, 9);
            starty = GetRandomNumberBetween(0, max);
            endx = startx;
            endy = starty + length - 1;
        }
        int success = field.placeShip(startx, starty, endx, endy);
        if (success) {
            return;
        }
    }
    throw std::logic_error("Generated impossible setup");
}

std::pair<int, int> findDamagedShip(Field &field) {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (field.isShot(x, y) && field.isShip(x, y)) {
                if (!field.isCompletelySunken(x, y)) {
                    return std::pair<int, int>(x, y);
                }
            }
        }
    }
    return std::pair<int, int>(-1, -1);
}

void shootRandomFreeCoordinate(Field &field) {
    while (true) {
        int x = GetRandomNumberBetween(0, 9);
        int y = GetRandomNumberBetween(0, 9);
        if (!field.isShot(x, y)) {
            field.shoot(x, y);
            return;
        }
    }
}

/**
 * Continues shooting in the direction until there is no ship or the board ends.
 * Return value signals if computer can make another move.
 */
bool continueShootingDirection(Field &field, int dir, int x, int y) {
    if (dir == 0) {
        if (x <= 0) return true; // left border reached
        x--;
    } else if (dir == 1) {
        if (x >= 9) return true; // right border reached
        x++;
    } else if (dir == 2) {
        if (y <= 0) return true; // upper border reached
        y--;
    } else {
        if (y >= 9) return true; // lower border reached
        y++;
    }
    if (field.isShot(x, y) && !field.isShip(x, y)) { // end of ship which was previously found
        return true;
    }
    field.shoot(x, y);
    if (field.isShip(x, y)) { // shot ship, continue shooting this direction
        return continueShootingDirection(field, dir, x, y);
    }
    return false; // no ship where the shot hit, move finished
}

void Computer::continueFindingShip(Field &field, int x, int y) {
    for (int i = 0; i < 4; i++) {
        bool moveFinished = !continueShootingDirection(field, i, x, y);
        if (moveFinished) {
            return;
        }
        if (field.isCompletelySunken(x, y)) {
            shoot(field);
            return;
        }
    }
}

void Computer::shoot(Field &enemyField) {
    std::pair<int, int> coords = findDamagedShip(field);
    if (coords.first == -1) {
        shootRandomFreeCoordinate(field);
    } else {
        continueFindingShip(field, coords.first, coords.second);
    }
}

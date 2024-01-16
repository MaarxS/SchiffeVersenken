#include "Computer.hpp"
#include "Field.hpp"
#include "CppRandom.hpp"

void Computer::placeShips(Field &field) {
    bool success = false;
    while (!success) {
        try {
            placeRandomShip(field, 5);
            placeRandomShip(field, 4);
            placeRandomShip(field, 4);
            placeRandomShip(field, 3);
            placeRandomShip(field, 3);
            placeRandomShip(field, 3);
            placeRandomShip(field, 2);
            placeRandomShip(field, 2);
            placeRandomShip(field, 2);
            placeRandomShip(field, 2);
            success = true;
        } catch (std::logic_error &e) {
            field.clear();
        }
    }
}

void Computer::placeRandomShip(Field &field, int length) {
    for (int i = 0; i < 100000; i++) {
        int max = 10 - length;
        int startx = 0;
        int starty;
        int endx;
        int endy;
        if (rand.GetRandomNumberBetween(0, 1)) {
            startx = rand.GetRandomNumberBetween(0, max);
            starty = rand.GetRandomNumberBetween(0, 9);
            endx = startx + length - 1;
            endy = starty;
        } else {
            startx = rand.GetRandomNumberBetween(0, 9);
            starty = rand.GetRandomNumberBetween(0, max);
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

bool Computer::shootRandomFreeCoordinate(Field &field) {
    int even[5] = {0, 2, 4, 6, 8};
    int odd[5] = {1, 3, 5, 7, 9};
    while (true) {
        int x = rand.GetRandomNumberBetween(0, 9);
        int y = rand.GetRandomNumberBetween(0, 4);
        if(x % 2){ //if odd
            y = odd[y];
        }else{ //even
            y = even[y];
        }
        if (!field.isShot(x, y)) {
            field.shoot(x, y);
            return field.isShip(x, y);
        }
    }
}

/**
 * Continues shooting in the direction until there is no ship or the board ends.
 * Return value signals if computer can make another move.
 */
bool continueShootingDirection(Field &field, int dir, int x, int y) {
    if (dir == 0) {
        if (x >= 9) return true; // right border reached
        x++;
    } else if (dir == 1) {
        if (x <= 0) return true; // left border reached
        x--;
    } else if (dir == 2) {
        if (y >= 9) return true; // lower border reached
        y++;
    } else {
        if (y <= 0) return true; // upper border reached
        y--;
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

bool Computer::guessOrientation(Field field, int x, int y) {
    if (x > 0 && field.isShot(x - 1, y) && field.isShip(x - 1, y) 
    || x < 9 && field.isShot(x + 1, y) && field.isShip(x + 1, y)) {
        std::cout << "horizontal\n";
        return 1;
    }
    if (y > 0 && field.isShot(x, y - 1) && field.isShip(x, y - 1) 
    || y < 9 && field.isShot(x, y + 1) && field.isShip(x, y + 1)) {
        std::cout << "vertcial\n";
        return 0;
    }
    return rand.GetRandomNumberBetween(0, 1);
}

void Computer::continueFindingShip(Field &field, int x, int y) {
    bool orientation = guessOrientation(field, x, y);
    for (int i = 0; i < 4; i++) {
        int dir = orientation ? i : (i + 2) % 4;
        bool moveFinished = !continueShootingDirection(field, dir, x, y);
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
    std::pair<int, int> coords = findDamagedShip(enemyField);
    if (coords.first == -1) {
        bool hit = shootRandomFreeCoordinate(enemyField);
        if (hit) {
            std::cout << "Der Bot hat getroffen! Er ist nochmal am Zug. \n";
            shoot(enemyField);
        }else{
            std::cout << "Der Bot hat nichts getroffen. \n";
        }
    } else if (true) {    //else?
        continueFindingShip(enemyField, coords.first, coords.second);
    }
}

#include "Computer.hpp"
#include "Field.hpp"
#include "CppRandom.hpp"

void Computer::placeShips() {
    for (int i = 1; i <= 4; i++) {
        int size = 6 - i;
        for (int j = 0; j < i; j++) {
            placeRandomShip(size);
            if(ownField->isBlocked()){
                ownField->clear();
                placeShips();
                return;
            }
        }
    }
}

void Computer::placeRandomShip(int length) {
    while(true) {  //needed?
        int max = 10 - length;
        int startx = 0;
        int starty;
        int endx;
        int endy;
        if (rand->getRandomNumberBetween(0, 1)) {
            startx = rand->getRandomNumberBetween(0, max);
            starty = rand->getRandomNumberBetween(0, 9);
            endx = startx + length - 1;
            endy = starty;
        } else {
            startx = rand->getRandomNumberBetween(0, 9);
            starty = rand->getRandomNumberBetween(0, max);
            endx = startx;
            endy = starty + length - 1;
        }
        int success = ownField->placeShip(startx, starty, endx, endy);
        if (success) {
            return;
        }
    }
}

std::pair<int, int> Computer::findDamagedShip() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (enemyField->isShot(x, y) && enemyField->isShip(x, y)) {
                if (!enemyField->isCompletelySunken(x, y)) {
                    return std::pair<int, int>(x, y);
                }
            }
        }
    }
    return std::pair<int, int>(-1, -1);
}

bool Computer::shootRandomFreeCoordinate() {
    int even[5] = {0, 2, 4, 6, 8};
    int odd[5] = {1, 3, 5, 7, 9};
    while (true) {
        int x = rand->getRandomNumberBetween(0, 9);
        int y;
        if(hardDifficulty){
            y = rand->getRandomNumberBetween(0, 4); //random element of array even/odd, sized 5
            if(x % 2){ //if odd
                y = odd[y];
            }else{ //even
                y = even[y];
            }
        }else{
            y = rand->getRandomNumberBetween(0, 9);
        }

        if (!enemyField->isShot(x, y)) {
            enemyField->shoot(x, y);
            if(enemyField->isShip(x, y)){
                std::cout << "Der Bot hat getroffen! Er ist nochmal am Zug. \n";
            }else{
                std::cout << "Der Bot hat nichts getroffen. \n";
            }
            return enemyField->isShip(x, y);
        }
    }
}

/**
 * Continues shooting in the direction until there is no ship or the board ends.
 * Return value signals if computer can make another move.
 */
bool Computer::continueShootingDirection(int dir, int x, int y) {
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
    if (enemyField->isShot(x, y) && !enemyField->isShip(x, y)) { // end of ship which was previously found
        return true;
    }
    enemyField->shoot(x, y);
    if (enemyField->isShip(x, y)) { // shot ship, continue shooting this direction
        std::cout << "Der Bot hat getroffen! Er ist nochmal am Zug. \n";
        return continueShootingDirection(dir, x, y);
    }else{
        std::cout << "Der Bot hat nichts getroffen. \n";
    }
    return false; // no ship where the shot hit, move finished
}

bool Computer::guessOrientation(int x, int y) {
    if (x > 0 && enemyField->isShot(x - 1, y) && enemyField->isShip(x - 1, y) 
    || x < 9 && enemyField->isShot(x + 1, y) && enemyField->isShip(x + 1, y)) {
        return 1;
    }
    if (y > 0 && enemyField->isShot(x, y - 1) && enemyField->isShip(x, y - 1) 
    || y < 9 && enemyField->isShot(x, y + 1) && enemyField->isShip(x, y + 1)) {
        return 0;
    }
    return rand->getRandomNumberBetween(0, 1);
}

void Computer::continueFindingShip(int x, int y) {
    bool orientation = guessOrientation(x, y);
    for (int i = 0; i < 4; i++) {
        int dir = orientation ? i : (i + 2) % 4;
        bool moveFinished = !continueShootingDirection(dir, x, y);
        if (moveFinished) {
            return;
        }
        if (enemyField->isCompletelySunken(x, y)) {
            if(!enemyField->isFinished()){ //dont shoot again if last ship is sunken
                std::cout << "Der Bot hat ein Schiff versenkt. \n";
                shoot();
            }
            return;
        }
    }
}

void Computer::shoot() {
    std::pair<int, int> coords = findDamagedShip();
    if (coords.first == -1) {
        bool hit = shootRandomFreeCoordinate();
        if (hit) {
            shoot();
        }
    } else {
        continueFindingShip(coords.first, coords.second);
    }
}

void Computer::setHardDifficulty(bool difficulty){
    hardDifficulty = difficulty;
}

bool Computer::getHardDifficulty(){
    return hardDifficulty;
}

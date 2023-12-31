#include <iostream>
#include "Field.hpp"

/**
 * Places a ship from start to end if allowed by the rules.
 * If succesfull it returns true, if not allowed it returns false.
 * (doesn't check for ship size)
*/
bool Field::placeShip(int startx, int starty, int endx, int endy) {
    if (startx != endx && starty != endy) { // not in one line
        return false;
    }
    for (int i = startx; i <= endx; i++) {
        for (int j = starty; j <= endy; j++) {
            if (isShipAdjacent(i, j)) { 
                return false;
            }
        }
    }
    for (int i = startx; i <= endx; i++) {
        for (int j = starty; j <= endy; j++) {
            field[i][j].placeShip();
        }
    }
    return true;
}

void Field::shoot(int x, int y) {
    field[x][y].shoot();
}

bool Field::isFinished() {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[j][i].isShip() && field[j][i].isShot()) {
                count++;
            }
        }
    }
    return count == 30;
}

void Field::printField(bool isOwnField) {
    std::cout << "  ";
    for (int i = 0; i <= 9; i++) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; i++) {
        char c = 'A' + i;
        std::cout << c << ' ';
        for (int j = 0; j < 10; j++) {
            Cell currentCell = field[j][i];
            bool isShot = currentCell.isShot();
            bool isShip = currentCell.isShip();
            if (isShip && isShot) {
                if (isCompletelySunken(j, i)) {
                    std::cout << "\x1B[30mX\033[0m"; //schwarz (versenktes Schiff)
                } else {
                    std::cout << "\x1B[31mX\033[0m"; //rot (getroffen, Schiff nicht versenkt)
                }
            } else if (isShot) {
                std::cout << "O"; //Schuss ins Meer
            } else if (isShip && isOwnField) {
                std::cout << "\xFE"; //weiß (plazierte Schiffe)
            } else {
                std::cout << "\x1B[36m\xFE\033[0m"; //blau (default Meer)
            }
            std::cout << ' ';
        }
        std::cout << c << ' ' << std::endl;
    }
    std::cout << "  ";
    for (int i = 0; i <= 9; i++) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

bool Field::isShipAdjacent(int x, int y) {
    int xstart = x >= 1 ? x - 1 : x;
    int xend   = x <= 8 ? x + 1 : x;
    int ystart = y >= 1 ? y - 1 : y;
    int yend   = y <= 8 ? y + 1 : y;
    int count = 0;
    for (int i = xstart; i <= xend; i++) {
        for (int j = ystart; j <= yend; j++) {
            if (field[i][j].isShip()) {
                return true;
            }
        }
    }
    return false;
}

bool Field::isCompletelySunken(int x, int y) {
    if (!field[x][y].isShip()) {
        return false;
    }
    for (int i = x; i >= 0; i--) {
        if (!field[i][y].isShip()) break;
        if (!field[i][y].isShot()) return false;
    }
    for (int i = x; i < 10; i++) {
        if (!field[i][y].isShip()) break;
        if (!field[i][y].isShot()) return false;
    }
    for (int i = y; i >= 0; i--) {
        if (!field[x][i].isShip()) break;
        if (!field[x][i].isShot()) return false;
    }
    for (int i = y; i < 10; i++) {
        if (!field[x][i].isShip()) break;
        if (!field[x][i].isShot()) return false;
    }
    return true;
}

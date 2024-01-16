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
            field[i][j].ship = true;
        }
    }
    return true;
}

void Field::clear() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            field[j][i].ship = false;
            field[j][i].hit = false;
        }
    }
}
bool Field::isClear(){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if(field[j][i].ship || field[j][i].hit){
                return false;
            }
        }
    }
    return true;
}

void Field::shoot(int x, int y) {
    field[x][y].hit = true;
    if (isCompletelySunken(x, y)) {
        shootAroundShip(x, y);
    }
}
void Field::setShip(int x, int y){
    field[x][y].ship = true;
}
void Field::setShot(int x, int y){
    field[x][y].hit = true;
}
bool Field::isShip(int x, int y) {
    return field[x][y].ship;
}
bool Field::isShot(int x, int y) {
    return field[x][y].hit;
}
bool Field::isFinished() {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[j][i].ship && field[j][i].hit) {
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
        char columnlabel = 'A' + i;
        std::cout << columnlabel << ' ';
        for (int j = 0; j < 10; j++) {
            if (field[j][i].ship && field[j][i].hit) {
                if (isCompletelySunken(j, i)) {
                    std::cout << "\x1B[30mX\033[0m"; //schwarz (versenktes Schiff)
                } else {
                    std::cout << "\x1B[31mX\033[0m"; //rot (getroffen, Schiff nicht versenkt)
                }
            } else if (field[j][i].hit) {
                std::cout << "O"; //Schuss ins Meer
            } else if (field[j][i].ship && isOwnField) {
                std::cout << "\xFE"; //weiß (plazierte Schiffe)
            } else {
                std::cout << "\x1B[36m\xFE\033[0m"; //blau (default Meer)
            }
            std::cout << ' ';
        }
        std::cout << columnlabel << ' ' << std::endl;
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
            if (field[i][j].ship) {
                return true;
            }
        }
    }
    return false;
}

bool Field::isCompletelySunken(int x, int y) {
    if (!field[x][y].ship) {
        return false;
    }
    for (int i = x; i >= 0; i--) {
        if (!field[i][y].ship) break;
        if (!field[i][y].hit) return false;
    }
    for (int i = x; i < 10; i++) {
        if (!field[i][y].ship) break;
        if (!field[i][y].hit) return false;
    }
    for (int i = y; i >= 0; i--) {
        if (!field[x][i].ship) break;
        if (!field[x][i].hit) return false;
    }
    for (int i = y; i < 10; i++) {
        if (!field[x][i].ship) break;
        if (!field[x][i].hit) return false;
    }
    return true;
}

void Field::shootAroundShip(int x , int y) {
    int xstart = x;
    int ystart = y;
    int xend = x;
    int yend = y;
    while (xstart > 0 && isShip(xstart, y)) {
        xstart--;
    }
    while (ystart > 0 && isShip(x, ystart)) {
        ystart--;
    }
    while (xend < 9 && isShip(xend, y)) {
        xend++;
    }
    while (yend < 9 && isShip(x, yend)) {
        yend++;
    }
    for (int i = xstart; i <= xend; i++) {
        for (int j = ystart; j <= yend; j++) {
            field[i][j].hit = true;
        }
    }
}

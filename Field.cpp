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
    for (int i = 0; i < fieldLimit; i++) {
        for (int j = 0; j < fieldLimit; j++) {
            field[j][i].ship = false;
            field[j][i].hit = false;
        }
    }
}
bool Field::isClear(){
    for (int i = 0; i < fieldLimit; i++) {
        for (int j = 0; j < fieldLimit; j++) {
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
    for (int i = 0; i < fieldLimit; i++) {
        for (int j = 0; j < fieldLimit; j++) {
            if (field[j][i].ship && field[j][i].hit) {
                count++;
            }
        }
    }
    return count == 30;
}

void Field::printField(bool isOwnField) {
    std::cout <<"   ";
    for (int i = 0; i < fieldLimit; i++) {
        std::cout << i <<" ";
        if(i < 10){
            std::cout <<" ";
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < fieldLimit; i++) {
        char columnLabel = 'A' + i;
        std::cout << columnLabel <<"  ";
        for (int j = 0; j < fieldLimit; j++) {
            if (field[j][i].ship && field[j][i].hit) {
                if (isCompletelySunken(j, i)) {
                    std::cout << "\x1B[30mX\033[0m "; //schwarz (versenktes Schiff)
                } else {
                    std::cout << "\x1B[31mX\033[0m "; //rot (getroffen, Schiff nicht versenkt)
                }
            } else if (field[j][i].hit) {
                std::cout << "O "; //Schuss ins Meer
            } else if (field[j][i].ship && isOwnField) {
                std::cout << "\xFE "; //weiß (plazierte Schiffe)
            } else {
                std::cout << "\x1B[36m\xFE\033[0m "; //blau (default Meer)
            }
            std::cout << ' ';
        }
        std::cout << columnLabel << ' ' << std::endl;
    }
    std::cout << "   ";
    for (int i = 0; i < fieldLimit; i++) {
        std::cout << i <<" ";
        if(i < 10){
            std::cout <<" ";
        }
    }
    std::cout << std::endl;
}

bool Field::isShipAdjacent(int x, int y) {
    int xstart = x >= 1 ? x - 1 : x;
    int xend   = x <= fieldLimit - 1 ? x + 1 : x;
    int ystart = y >= 1 ? y - 1 : y;
    int yend   = y <= fieldLimit - 1 ? y + 1 : y;
    int count = 0;
    for (int i = xstart; i <= xend; i++) {
        for (int j = ystart; j <= yend; j++) {
            std::cout << j << " " << i << std::endl;
            if (field[i][j].ship) {
                std::cout << j << " :(" << i << std::endl;
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

bool Field::isBlocked(){ //true if no 2*2 ship fits anywhere
    bool squareBlocked[8] = {false, false, false, false, false, false, false, false};
    for(int i = 0; i < 8; i++){         //move this 3*4 square 8 times to the right and 7 times downwards, to cover the whole field
        for(int j = 0; j < 7; j++){
            for(int k = 0; k < 3; k++){         //check 3*4 fieldsize for ships (ships with no connection to the border)
                for(int l = 0; l < 4; l++){
                    if(isShip(i + k, j + l)) squareBlocked[0] = true; //vertical
                    if(isShip(j + l, i + k)) squareBlocked[1] = true; // same thing, sideways 4*3 block, 7 right 8 down (horizontal)
                }
            }
            if(!squareBlocked[0] || !squareBlocked[1]){
                return false;
            } 
            squareBlocked[0] = false;
            squareBlocked[1] = false;
        }
     }
     //edges 4*2
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 4; k++){ //2*4 block
                if(isShip(0 + j, i + k)) squareBlocked[0] = true; //left edge
                if(isShip(9 - j, i + k)) squareBlocked[1] = true; //right edge
                if(isShip(i + k, 0 + j)) squareBlocked[2] = true; //top edge
                if(isShip(i + k, 8 + j)) squareBlocked[3] = true; //bottom edge
            }
        }
        for(int i = 0; i < 4; i++){
             if(!squareBlocked[i]){
                return false;
            } 
            squareBlocked[i] = false;
        }   
    }
    //edges 3*3
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){ //3*3 block
                if(isShip(0 + j, i + k)) squareBlocked[0] = true; //left edge
                if(isShip(9 - j, i + k)) squareBlocked[1] = true; //right edge
                if(isShip(i + j, 0 + k)) squareBlocked[2] = true; //top edge
                if(isShip(i + j, 9 - k)) squareBlocked[3] = true; //bottom
            }
        }
        for(int i = 0; i < 4; i++){
            if(!squareBlocked[i]){
                return false;
            } 
            squareBlocked[i] = false;
        }
    }
    //corners
    for(int i = 0; i < 3; i++){  //3*2 block
        for(int j = 0; j < 2; j++){
            if(isShip(0 + i, 0 + j)) squareBlocked[0] = true; //top left horizontal
            if(isShip(0 + j, 0 + i)) squareBlocked[1] = true; //top left vertical

            if(isShip(9 - i, 9 - j)) squareBlocked[2] = true; //bottom right horizontal
            if(isShip(9 - j, 9 - i)) squareBlocked[3] = true; //bottom right vertical

            if(isShip(0 + i, 9 - j)) squareBlocked[4] = true; //bottom left horizontal
            if(isShip(0 + j, 9 - i)) squareBlocked[5] = true; //bottom left vertical

            if(isShip(9 - i, 0 + j)) squareBlocked[6] = true; //top right horizontal
            if(isShip(9 - j, 0 + i)) squareBlocked[7] = true; //top right vertical
        }
    }
    for(int i = 0; i < 8; i++){
        if(!squareBlocked[i]){
            return false;
        } 
        squareBlocked[i] = false;
    }
    return true;
}

int Field::getFieldLimit(){
    return fieldLimit;
}

void Field::setFieldLimit(int limit){
    fieldLimit = limit;
}

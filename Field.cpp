#include <iostream>
#include "Field.hpp"

Field::Field() {
    field[4][5].placeShip();
}

void Field::printField(bool isOwnField) {
    std::cout << "  ";
    for (int i = 1; i <= 10; i++) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; i++) {
        char c = 'A' + i;
        std::cout << c << ' ';
        for (int j = 0; j < 10; j++) {
            Cell currentCell = field[i][j];
            if (currentCell.isMissedShot()) {
                std::cout << "O"; //Schuss ins Meer
            } else if (currentCell.isHitShip()) {
                std::cout << "\x1B[31mX\033[0m"; //rot (getroffen, Schiff nicht versenkt)
            } else if (currentCell.isShip() && isOwnField) {
                std::cout << "\xFE"; //weiß (plazierte Schiffe)
            } else {
                std::cout << "\x1B[36m\xFE\033[0m"; //blau (default Meer)
            }
            std::cout << ' ';
        }
        std::cout << c << ' ' << std::endl;
    }
    std::cout << "  ";
    for (int i = 1; i <= 10; i++) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}


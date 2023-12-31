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
            std::cout << e.what() << " retrying" << std::endl;
            field.printField(true);

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

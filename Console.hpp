#pragma once
#include <string>

typedef struct Coordinates {
    int x;
    int y;
} coordinates_t;

typedef struct Ship {
    coordinates_t start;
    coordinates_t end;
} ship_t;

class Console {

    void printMenu(bool withMidgameOption);
    int numberInput(int min, int max);
    bool isDigit(std::string &str);
    

    public:
    enum Mode {STOP_PROGRAM, NEW_GAME, LOAD_GAME, SAVE_GAME, CONTINUE_GAME};
    Mode menuInput(bool withMidgameOption);
    ship_t shipInput(int size, int count);
    coordinates_t coordinateInput(bool stopAllowed);
    bool botDifficulty();
    
};

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

    void print_menu(bool with_midgame_option);
    int number_input(int min, int max);
    bool is_digits(std::string &str);
    

    public:
    void print_image();
    int menu_input(bool with_midgame_option);
    ship_t ship_input(int size);
    coordinates_t coordinateInput(bool stop_allowed);
    enum Mode {STOP_PROGRAM, NEW_GAME, LOAD_GAME, SAVE_GAME, CONTINUE_GAME};
};

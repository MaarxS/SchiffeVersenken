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
    inline static const int STOP_PROGRAM = 0;
    inline static const int NEW_GAME = 1;
    inline static const int LOAD_GAME = 2;
    inline static const int SAVE_GAME = 3;
    inline static const int CONTINUE_GAME = 4;
};
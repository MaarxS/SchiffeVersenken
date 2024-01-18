#pragma once
#include "Field.hpp"
#include "CppRandom.hpp"
#include "Computer.hpp"
#include "Console.hpp"
#include "Save.hpp"
#include <memory>

class Controller {
    std::shared_ptr<Field> playerfield;
    std::shared_ptr<Field> botfield;   
    std::shared_ptr<Random> random;
    std::unique_ptr<Computer> computer;
    std::unique_ptr<Console> console;
    std::unique_ptr<Save> save;

    bool menu(Console::Mode mode);
    void new_game();
    void player_place_all_ships();
    void player_place_ship(int size);
    void start_first_move();
    void game_loop();

    public:
    Controller();
    void start();
};

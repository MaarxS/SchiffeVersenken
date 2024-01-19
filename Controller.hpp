#pragma once
#include "Field.hpp"
#include "CppRandom.hpp"
#include "Computer.hpp"
#include "Console.hpp"
#include "Save.hpp"
#include <memory>

class Controller {
    std::shared_ptr<Field> playerField;
    std::shared_ptr<Field> botField;   
    std::shared_ptr<Random> random;
    std::unique_ptr<Computer> computer;
    std::unique_ptr<Console> console;
    std::unique_ptr<Save> save;

    bool menu(Console::Mode mode);
    void newGame();
    void playerPlaceAllShips();
    void playerPlaceShip(int size, int count);
    void startFirstMove();
    void gameLoop();

    public:
    Controller();
    void start();
};

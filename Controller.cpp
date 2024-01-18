#include "Controller.hpp"

int main() {
    Controller controller;
    controller.start();
}

Controller::Controller() {
    playerfield = std::make_shared<Field>();
    botfield = std::make_shared<Field>();
    random = std::make_shared<Random>();
    computer = std::make_unique<Computer>(random, botfield, playerfield);
    console = std::make_unique<Console>();
    save = std::make_unique<Save>();
}

void Controller::start() {
    console->print_image();
    while (true) {
        bool is_midgame = !(playerfield->isClear() || playerfield->isFinished() || botfield->isFinished());
        int mode = console->menu_input(is_midgame);
        bool in_menu = menu((Console::Mode) mode);
        if (!in_menu) {
            game_loop();
        }
    }
}

/** 
 * Executes the action the user chose in the menu.
 * 
 * Returns true if the menu should be displayed again and false if it should 
 * continue with the game loop.
*/
bool Controller::menu(Console::Mode mode) {
    bool save_success;
    std::string filename;
    switch(mode){
        case Console::STOP_PROGRAM:
            exit(0);
        case Console::NEW_GAME:
            new_game();
            return false;
        case Console::LOAD_GAME:
            std::cout << "Bitte geben Sie den Dateinamen ein:" <<  std::endl;
            std::cin >> filename;
            save_success = save->loadGame(*playerfield, *botfield, filename);
            return !save_success;
        case Console::SAVE_GAME:
            std::cout << "Bitte geben Sie den gewuenschten Dateinamen ein:" <<  std::endl;
            std::cin >> filename;
            save->saveGame(*playerfield, *botfield, filename);
            if(save_success){
                std::cout << "Die Datei wurde erfolgreich unter "<< filename << ".SVgame gespeichert."<<  std::endl;
            }else{
                std::cout << "Es ist ein Fehler beim Speichern aufgetreten. Bitte achten Sie auf einen gueltigen Dateinamen und versuchen Sie es erneut." <<  std::endl; 
            }
            return true;
        case Console::CONTINUE_GAME:
            return false;
        default:
            return true;
    }
    return true;
}

void Controller::new_game() {
    playerfield->clear();
    botfield->clear();
    computer->placeShips();
    player_place_all_ships();
    start_first_move();
}

void Controller::player_place_all_ships() {
    char reset;
    for (int i = 1; i <= 4; i++) {
        int size = 6 - i;
        for (int j = 0; j < i; j++) {
            playerfield->printField(true);
            player_place_ship(size);
            if(size == 2 && playerfield->isBlocked()){    //Überprüfe bei allen U-Booten(2) ob der Benutzer sich selbst blockiert hat und nicht mehr weiter kommt
                std::cout << "Sie haben das restliche Spielfeld blockiert. Um erneut zu starten druecken Sie eine beliebige Taste." << std::endl;
                playerfield->clear();
                player_place_all_ships();
                return;
            }
        }
    }
}

void Controller::player_place_ship(int size) {
    bool input_correct;
    do {
        auto ship = console->ship_input(size);
        input_correct = playerfield->placeShip(ship.start.x, ship.start.y, ship.end.x, ship.end.y); // Überprüfung auf Fehler gegen die Spiellogik // TODO replace with struct
        if (!input_correct) {
            std::cout << "Bitte achten Sie darauf, dass die Schiffe sich nicht schneiden, beruehren oder diagonal platziert werden. " << std::endl;
        }
    } while (!input_correct);
}

/** For the first move it needs to be evaluated who starts. */
void Controller::start_first_move() {
    if(random->GetRandomNumberBetween(0, 1)){
        std::cout << "Der Bot beginnt. \n";
        computer->shoot();
    }else{
        std::cout << "Sie duerfen anfangen. \n";
    }
}

void Controller::game_loop() {
    while(true){
        bool anothermove = true;
        while(anothermove){
            std::cout << std::endl;
            std::cout << "Ihr Feld:" << std::endl;
            playerfield->printField(true);
            std::cout << std::endl;
            std::cout << "Gegnerisches Feld:" << std::endl;
            botfield->printField(false);
            std::cout << "Bitte geben Sie Ihre Zielkoordinaten an." << std::endl;
            auto coord = console->coordinateInput(true);
            if(coord.x == -1 && coord.y == -1){
                return;
            }
            if(botfield->isShot(coord.x, coord.y)){
                std::cout << "Dieses Feld hatten Sie bereits als Ziel. Bitte waehlen Sie ein freies Feld." << std::endl;
                continue;

            }
            botfield->shoot(coord.x, coord.y);
            if(botfield->isShip(coord.x, coord.y)){
                std::cout << "Sie haben getroffen! Sie sind nochmal dran. \n";
                if(botfield->isCompletelySunken(coord.x, coord.y)){
                    std::cout << "Sie haben das gesamte Schiff versenkt. \n";
                }
            }else{
                std::cout << "Sie haben nichts getroffen. \n";
            }
            if(botfield->isFinished()) {
                std::cout << std::endl;
                std::cout << "Ihr Feld:" << std::endl;
                playerfield->printField(true);
                std::cout << std::endl;
                std::cout << "Gegnerisches Feld:" << std::endl;
                botfield->printField(false);
                std::cout << "Du hast gewonnen!\n";
                return;
            }
            anothermove = botfield->isShip(coord.x, coord.y);
        }
        computer->shoot();
        if(playerfield->isFinished()){
            std::cout << std::endl;
            std::cout << "Ihr Feld:" << std::endl;
            playerfield->printField(true);
            std::cout << std::endl;
            std::cout << "Gegnerisches Feld:" << std::endl;
            botfield->printField(false);
            std::cout << "Du hast verloren.\n";
            return;
        }
    }
}

#include "Controller.hpp"

int main() {
    Controller controller;
    controller.start();
}

Controller::Controller() {
    playerField = std::make_shared<Field>();
    botField = std::make_shared<Field>();
    random = std::make_shared<Random>();
    computer = std::make_unique<Computer>(random, botField, playerField);
    console = std::make_unique<Console>();
    save = std::make_unique<Save>();
}

void Controller::start() {
    while (true) {
        bool isMidGame = !(playerField->isClear() || playerField->isFinished() || botField->isFinished());
        Console::Mode mode = console->menuInput(isMidGame);
        bool inMenu = menu(mode);
        if (!inMenu) {
            gameLoop();
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
    bool saveSuccess;
    bool hardBot;
    std::string fileName;
    switch(mode){
        case Console::STOP_PROGRAM:
            exit(0);
        case Console::NEW_GAME:
            hardBot = console->botDifficulty();
            computer->setHardDifficulty(hardBot);
            newGame();
            return false;
        case Console::LOAD_GAME:
            std::cout << "Bitte geben Sie den Dateinamen ein:" <<  std::endl;
            std::cin >> fileName;
            saveSuccess = save->loadGame(playerField, botField, fileName);
            if(saveSuccess){
                hardBot = save->loadDifficulty(fileName);
                computer->setHardDifficulty(hardBot);
                std::cout << "Die Datei wurde erfolgreich geladen." << std::endl;
            }else{
                std::cout << "Die Datei konnte nicht gefunden werden." << std::endl;
            }
            return !saveSuccess;
        case Console::SAVE_GAME:
            std::cout << "Bitte geben Sie den gewuenschten Dateinamen ein:" <<  std::endl;
            std::cin >> fileName;
            saveSuccess = save->saveGame(playerField, botField, fileName, computer->getHardDifficulty());
            if(saveSuccess){
                std::cout << "Die Datei wurde erfolgreich unter "<< fileName << ".SVgame gespeichert."<<  std::endl;
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

void Controller::newGame() {
    playerField->clear();
    botField->clear();
    computer->placeShips();
    playerPlaceAllShips();
    startFirstMove();
}

void Controller::playerPlaceAllShips() {
    for (int i = 1; i <= 4; i++) {
        int size = 6 - i;
        for (int j = 0; j < i; j++) {
            playerField->printField(true);
            playerPlaceShip(size, j + 1);
            if(size == 2 && playerField->isBlocked() && j != 3){    //Überprüfe bei allen U-Booten(2) ob der Benutzer sich selbst blockiert hat und nicht mehr weiter kommt
                std::cout << "Sie haben das restliche Spielfeld blockiert. Das Platzieren wird neu gestartet." << std::endl;
                playerField->clear();
                playerPlaceAllShips();
                return;
            }
        }
    }
}

void Controller::playerPlaceShip(int size, int count) {
    bool inputCorrect;
    do {
        auto ship = console->shipInput(size, count);
        inputCorrect = playerField->placeShip(ship.start.x, ship.start.y, ship.end.x, ship.end.y); // Überprüfung auf Fehler gegen die Spiellogik
        if (!inputCorrect) {
            std::cout << "Bitte achten Sie darauf, dass die Schiffe sich nicht schneiden, beruehren oder diagonal platziert werden. " << std::endl;
        }
    } while (!inputCorrect);
}

/** For the first move it needs to be evaluated who starts. */
void Controller::startFirstMove() {
    if(random->getRandomNumberBetween(0, 1)){
        std::cout << "Der Bot beginnt. \n";
        computer->shoot();
    }else{
        std::cout << "Sie duerfen anfangen. \n";
    }
}

void Controller::gameLoop() {
    while(true){
        bool anotherMove = true;
        while(anotherMove){
            std::cout << std::endl;
            std::cout << "Ihr Feld:" << std::endl;
            playerField->printField(true);
            std::cout << std::endl;
            std::cout << "Gegnerisches Feld:" << std::endl;
            botField->printField(false);
            std::cout << "Bitte geben Sie Ihre Zielkoordinaten an." << std::endl;
            auto coord = console->coordinateInput(true);
            if(coord.x == -1 && coord.y == -1){
                return;
            }
            if(botField->isShot(coord.x, coord.y)){
                std::cout << "Dieses Feld hatten Sie bereits als Ziel. Bitte waehlen Sie ein freies Feld." << std::endl;
                continue;

            }
            botField->shoot(coord.x, coord.y);
            if(botField->isShip(coord.x, coord.y)){
                std::cout << "Sie haben getroffen! Sie sind nochmal dran. \n";
                if(botField->isCompletelySunken(coord.x, coord.y)){
                    std::cout << "Sie haben das gesamte Schiff versenkt. \n";
                }
            }else{
                std::cout << "Sie haben nichts getroffen. \n";
            }
            if(botField->isFinished()) {
                std::cout << std::endl;
                std::cout << "Ihr Feld:" << std::endl;
                playerField->printField(true);
                std::cout << std::endl;
                std::cout << "Gegnerisches Feld:" << std::endl;
                botField->printField(false);
                std::cout << "Du hast gewonnen!\n";
                return;
            }
            anotherMove = botField->isShip(coord.x, coord.y);
        }
        computer->shoot();
        if(playerField->isFinished()){
            std::cout << std::endl;
            std::cout << "Ihr Feld:" << std::endl;
            playerField->printField(true);
            std::cout << std::endl;
            std::cout << "Gegnerisches Feld:" << std::endl;
            botField->printField(false);
            std::cout << "Du hast verloren.\n";
            return;
        }
    }
}

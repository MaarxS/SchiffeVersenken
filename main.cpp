#include "Field.hpp"
#include "Save.hpp"
#include "Computer.hpp"
#include "CppRandom.hpp"
#include <iostream>
#include <cmath>

void getPlayerInput(Field &playerfield);
bool checkPlayerInput(Field &playerfield, std::pair<int, int> &start_coord, std::pair<int, int> &end_coord, int expected_size);
std::pair<int, int> coordinateInput(bool stop_allowed);
void menu(Field &playerfield, Field &botfield, Computer &com);
void gameLoop(Field &playerfield, Field &botfield, Computer &com);

int main() {
    
    Field playerfield;
    Field botfield;
    Computer com;
    
    while(true){
        menu(playerfield, botfield, com); 
        gameLoop(playerfield, botfield, com);
    }
}


void gameLoop(Field &playerfield, Field &botfield, Computer &com) {
    Random rand;
    if (rand.GetRandomNumberBetween(0, 1)) {
        com.shoot(playerfield);
    }
    while (true) {
        bool anothermove = true;
        while (anothermove) {
            playerfield.printField(true);
            botfield.printField(false);
            std::cout << "Bitte geben Sie Ihre Zielkoordinaten an." << std::endl;
            auto coord = coordinateInput(true);
            if(coord.first == -1 && coord.second == -1){
                return;
            }
            botfield.shoot(coord.first, coord.second);
            if (botfield.isFinished()) {
                playerfield.printField(true);
                botfield.printField(false);
                std::cout << "Du hast gewonnen!\n";
                return;
            }
            anothermove = botfield.isShip(coord.first, coord.second);
        }
        com.shoot(playerfield);
        if (playerfield.isFinished()) {
            playerfield.printField(true);
            botfield.printField(false);
            std::cout << "Du hast verloren.\n";
            return;
        }
    }

}


void getPlayerInput(Field &playerfield){

    std::pair<int, int> coordinates_start;
    std::pair<int, int> coordinates_end;

    bool number_correct = false;

    do{
        std::cout << "Bitte geben Sie die Startposition ihres Schlachtschiffes (5) an: " << std::endl;
        coordinates_start = coordinateInput(false);
        std::cout << "Bitte geben Sie die Endposition ihres Schlachtschiffes (5) an: " << std::endl;
        coordinates_end = coordinateInput(false);

        number_correct = checkPlayerInput(playerfield, coordinates_start, coordinates_end, 5);
    }while(!number_correct);

    for(int i = 0; i < 2; i++){
        do{
            std::cout << "Bitte geben Sie die Startposition ihres " << i + 1 << " .Kreuzers (4) an: " << std::endl;
            coordinates_start = coordinateInput(false);
            std::cout << "Bitte geben Sie die Endposition ihres " << i + 1 << " .Kreuzers (4) an: " << std::endl;
            coordinates_end = coordinateInput(false);

            number_correct = checkPlayerInput(playerfield, coordinates_start, coordinates_end, 4);
        }while(!number_correct);
    }

    for(int i = 0; i < 3; i++){
        do{
            std::cout << "Bitte geben Sie die Startposition ihres " << i + 1 << " .Zerstoerers (3) an: " << std::endl;
            coordinates_start = coordinateInput(false);
            std::cout << "Bitte geben Sie die Endposition ihres " << i + 1 << " .Zerstoerers (3) an: " << std::endl;
            coordinates_end = coordinateInput(false);

            number_correct = checkPlayerInput(playerfield, coordinates_start, coordinates_end, 3);
        }while(!number_correct);
    }

    for(int i = 0; i < 4; i++){
        do{
            std::cout << "Bitte geben Sie die Startposition ihres " << i + 1 << " .U-Boots (2) an: " << std::endl;
            coordinates_start = coordinateInput(false);
            std::cout << "Bitte geben Sie die Endposition ihres " << i + 1 << " .U-Boots (2) an: " << std::endl;
            coordinates_end = coordinateInput(false);

            number_correct = checkPlayerInput(playerfield, coordinates_start, coordinates_end, 2);
        }while(!number_correct);
    }
}

bool checkPlayerInput(Field &playerfield, std::pair<int, int> &start_coord, std::pair<int, int> &end_coord, int expected_size) {
    int x_value_start = start_coord.first;
    int y_value_start = start_coord.second;
    int x_value_end = end_coord.first;
    int y_value_end = end_coord.second;
    int length_x;
    int length_y;

    length_x = abs(x_value_start - x_value_end);
    length_y = abs(y_value_start - y_value_end);

    if(length_x != (expected_size - 1) && length_y != (expected_size - 1)){
        std::cout << "Bitte geben Sie ein Schiff der Laenge " << expected_size << " an. "<<std::endl;
        return false;
    }
    int swap;
    if(y_value_start > y_value_end){
        swap = y_value_start;
        y_value_start = y_value_end;
        y_value_end = swap;
        
    }else if(x_value_start > x_value_end){
        swap = x_value_start;
        x_value_start = x_value_end;
        x_value_end = swap;
    }
    
    if(!playerfield.placeShip(x_value_start, y_value_start, x_value_end, y_value_end)){
        std::cout << "Bitte achten Sie darauf, dass die Schiffe sich nicht schneiden, beruehren oder diagonal platziert werden. " << std::endl;
        return false;
    }

    playerfield.printField(true);
    return true;
}

std::pair<int, int> coordinateInput(bool stop_allowed){
    std::string coordinates;
    int x_value;
    int y_value;
    std::string error_message = "Bitte geben Sie Koordinaten bestehend aus einem Buchstabe von A-J und einer Ziffer von 0-9 an.\n";

    while (true) {
        std::cin >> coordinates;
        if (coordinates == "stop" && stop_allowed) {
            return std::pair<int, int>(-1, -1);
        }
        if(coordinates.length() != 2){
            std::cout << error_message;
            continue;
        }
        if(isdigit(coordinates[0])){
            x_value = coordinates[0] - '0';
            coordinates[1] = std::tolower(coordinates[1]);
            y_value = coordinates[1]- 'a';
        }else if(isdigit(coordinates[1])){
             x_value = coordinates[1] - '0';
            coordinates[0] = std::tolower(coordinates[0]);
            y_value = coordinates[0] - 'a';
        }else{
            std::cout << error_message;
            continue;
        }
        if(x_value > 9 || x_value < 0 || y_value > 9 || y_value < 0){
            std::cout << error_message;
            continue;
        }
        return std::pair<int, int>(x_value, y_value);
    }
}
void menu(Field &playerfield, Field &botfield, Computer &com){
    Save safe;
    int mode = 0;
    bool mode_success = false;
    std::string filename;
    do{
        std::cout << "Bitte waehlen Sie eine Option aus:" << std::endl;
        std::cout << "Neues Spiel starten (1)" << std::endl;
        std::cout << "Altes Spiel vortsetzen (2)" << std::endl;
        std::cout << "aktuelles Spiel Speichern (3)" << std::endl;
        std::cout << "Programm beenden (4)" << std::endl;
        std::cout << "Sie koennen nach dem platzieren Ihrer Schiffe ueber die Eingabe \'stop\' ins Hauptmenue zurueck." << std::endl;
        std::cin >> mode;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(mode){
            case 1:
                mode_success = true;
                playerfield.clear();
                botfield.clear();
                com.placeShips(botfield);
                playerfield.printField(true);
                getPlayerInput(playerfield);
                break;
            case 2:
                std::cout << "Bitte geben Sie den Dateinamen ein:" <<  std::endl;
                std::cin >> filename;
                mode_success = safe.loadGame(playerfield, botfield, filename);
                break;
            case 3:
                if(playerfield.isClear()){
                    mode_success = false;
                    std::cout << "Sie koennen kein Feld speichern, ohne vorher Schiffe zu platzieren." << std::endl;
                    break;
                }
                std::cout << "Bitte geben Sie den gewuenschten Dateinamen ein:" <<  std::endl;
                std::cin >> filename;
                mode_success = safe.saveGame(playerfield, botfield, filename);
                if(mode_success){
                    std::cout << "Die Datei wurde erfolgreich unter "<< filename << ".SVgame gespeichert."<<  std::endl;
                    mode_success = false;
                }else{
                   std::cout << "Es ist ein Fehler beim Speichern aufgetreten. Bitte achten Sie auf einen gueltigen Dateinamen und versuchen Sie es erneut." <<  std::endl; 
                }
                break;
            case 4:
                exit(0);
                break;
            default:
                mode_success = false;
                break;
        }
    }while(!mode_success);
    
}

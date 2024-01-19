#include "Console.hpp"
#include <iostream>

/**
 * Prints the menu and asks the user for a choice.
 * 
 * The result is STOP_PROGRAM, NEW_GAME, LOAD_GAME, SAVE_GAME or CONTINUE_GAME
 * The last two options are midgame options and only possible if withMidgameOptions is true
*/
Console::Mode Console::menuInput(bool withMidgameOptions) {
    printMenu(withMidgameOptions);
    int max = withMidgameOptions ? 4 : 2;
    return (Mode) numberInput(0, max);
}

void Console::printMenu(bool withMidgameOptions) {
    std::cout << std::endl;
    std::cout << "Bitte waehlen Sie eine Option aus:" << std::endl;
    std::cout << "Programm beenden (0)" << std::endl;
    std::cout << "Neues Spiel starten (1)" << std::endl;
    std::cout << "Altes Spiel fortsetzen (2)" << std::endl;
    if (withMidgameOptions) {
        std::cout << "Aktuelles Spiel speichern (3)" << std::endl;
        std::cout << "Aktuelles Spiel fortsetzen (4)" << std::endl;
    }
    std::cout << "Sie koennen nach dem platzieren Ihrer Schiffe ueber die Eingabe \'stop\' ins Hauptmenue zurueck." << std::endl;
}

/** Asks the user for a number input which must be between min and max inclusive. */
int Console::numberInput(int min, int max) {
    std::string errorMessage = "Geben Sie eine Ziffer zwischen " + std::to_string(min) + " und " + std::to_string(max) + " ein.\n";
    while (true) {
        std::string input;
        std::cin >> input;
        if (!isDigit(input)) {
            std::cout << errorMessage;
            continue;
        }
        int num = std::stoi(input);
        if (num < min || num > max) {
            std::cout << errorMessage;
            continue;
        }
        return num;
    }
}

bool Console::isDigit(std::string &str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

/**
 * Asks the user to input two coordinates marking the start and end of a boat.
 * 
 * The boat returns always has the smaller coordinates first and the size is ensured.
*/
ship_t Console::shipInput(int size, int count, int fieldsize) {
    std::string shipName;
    if (size == 5) {
        shipName = "Schlachtschiffes";
    } else if (size == 4) {
        shipName = "Kreuzers";
    } else if (size == 3) {
        shipName = "Zerstoerers";
    } else {
        shipName = "U-Boots";
    }
    coordinates_t start;
    coordinates_t end;
    while (true) {
        std::cout << "Bitte geben Sie die Startposition ihres "<< count << ". " << shipName << " (" << size << ") an: " << std::endl;
        start = coordinateInput(false, fieldsize);
        std::cout << "Bitte geben Sie die Endposition ihres " << count << ". " << shipName << " (" << size << ") an: " << std::endl;
        end = coordinateInput(false, fieldsize);

        int swap;               // Sortierung der Koordinatenwerte nach Größe
        if(start.y > end.y) {
            swap = start.y;
            start.y = end.y;
            end.y = swap;
        } else if(start.x > end.x) {
            swap = start.x;
            start.x = end.x;
            end.x = swap;
        }

        if (end.x - start.x + 1 != size && end.y - start.y + 1 != size) {
            std::cout << "Bitte geben Sie ein Schiff der Laenge " << size << " an. "<<std::endl;
        } else {
            break;
        }
    }
    ship_t boat = {start, end};
    return boat;
}

/**
 * Asks the user for one coordinate on a 10x10 field.
 * 
 * Returns {-1, -1} if the user entered stop and stopAllowed is true.
 * Otherwise returns the coordinate.
*/
coordinates_t Console::coordinateInput(bool stopAllowed, int limit){
    std::string coordinates;
    int xValue;
    int yValue;
    std::string errorMessage = "Bitte geben Sie Koordinaten bestehend aus einem Buchstabe von A-J und einer Ziffer von 0-" + std::to_string(limit -1) + " an.\n";

    while(true){
        std::cin >> coordinates;
        if(coordinates == "stop" && stopAllowed) {
            return {-1, -1};
        }
        if(coordinates.length() == 3){
            std::string substr1 = coordinates.substr(0,2);
            std::string substr2 = coordinates.substr(1,2);
            if(isDigit(substr1)){
                xValue = std::stoi(substr1);
                coordinates[2] = std::tolower(coordinates[2]);
                yValue = coordinates[2] - 'a';
            }else if(isDigit(substr2)){
                xValue = std::stoi(substr2);
                coordinates[0] = std::tolower(coordinates[0]);
                yValue = coordinates[0] - 'a';
            }else{
                std::cout << errorMessage;
                continue;
            }
        }else if(coordinates.length() == 2){
            if(isdigit(coordinates[0])){
                xValue = coordinates[0] - '0';
                coordinates[1] = std::tolower(coordinates[1]);
                yValue = coordinates[1]- 'a';
            }else if(isdigit(coordinates[1])){
                xValue = coordinates[1] - '0';
                coordinates[0] = std::tolower(coordinates[0]);
                yValue = coordinates[0] - 'a';
            }else{
                std::cout << errorMessage;
                continue;
            }
        }else{
            std::cout << errorMessage;
            continue;
        }
        if(xValue > (limit -1) || xValue < 0 || yValue > (limit -1) || yValue < 0){
            std::cout << errorMessage;
            continue;
        }
        std::cout << xValue << " " << yValue << std::endl;
        return {xValue, yValue};
    }
}
bool Console::botDifficulty(){

    std::cout << "Bitte geben Sie die Schwierigkeit des Bots ein: " <<  std::endl;
    std::cout << "Leicht (1) " <<  std::endl;
    std::cout << "Schwer (2) " <<  std::endl;
   
    int difficulty = numberInput(1, 2);
    if(difficulty == 2){
        return true;
    }
    return false;
}
int Console::fieldSize(){
    std::cout << "Bitte geben Sie die Kantenlaenge des Feldes an: " <<  std::endl;
    int size = numberInput(2, 25);
    return size;
}

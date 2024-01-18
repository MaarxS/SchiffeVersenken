#include "Console.hpp"
#include <iostream>

/** Print a small ASCII image. */
void Console::print_image() {
    std::cout << "      |    |    |      v                     " << std::endl;
    std::cout << "     )_)  )_)  )_)                    v      " << std::endl;
    std::cout << "    )___))___))___)\\            ~.          " << std::endl;
    std::cout << "   )____)____)_____)\\      v    /|          " << std::endl;
    std::cout << " _____|____|____|____\\\\__      / |         " << std::endl;
    std::cout << "-\\                   /--------/__|__--------" << std::endl;
    std::cout << "^^^^^^^^^^^^^^^^^^^^^     ^ \\--------/  ^^  " << std::endl;
    std::cout << "     ^^   _    _^^^     ^^^  \"^^^^^^\"    ^" << std::endl;
    std::cout << "^      __|_|__|_|__^^   ^^^    ^^     ^^^^^  " << std::endl;
    std::cout << " ^^  _|____________|__      ^^^^   ^^^    ^  " << std::endl;
    std::cout << "    | o o o o o o o o /  ^^     ^^^^    ^^   " << std::endl;
    std::cout << "  ^^^^^^^^^^^^^^^^^^^^       ^^    ^^^   ^^  " << std::endl;
}

/**
 * Prints the menu and asks the user for a choice.
 * 
 * The result is STOP_PROGRAM, NEW_GAME, LOAD_GAME, SAVE_GAME or CONTINUE_GAME
 * The last two options are midgame options and only possible if with_midgame_options is true
*/
int Console::menu_input(bool with_midgame_options) {
    print_menu(with_midgame_options);
    int max = with_midgame_options ? 4 : 2;
    return number_input(0, max);
}

void Console::print_menu(bool with_midgame_options) {
    std::cout << std::endl;
    std::cout << "Bitte waehlen Sie eine Option aus:" << std::endl;
    std::cout << "Programm beenden (0)" << std::endl;
    std::cout << "Neues Spiel starten (1)" << std::endl;
    std::cout << "Altes Spiel fortsetzen (2)" << std::endl;
    if (with_midgame_options) {
        std::cout << "Aktuelles Spiel speichern (3)" << std::endl;
        std::cout << "Aktuelles Spiel fortsetzen (4)" << std::endl;
    }
    std::cout << "Sie koennen nach dem platzieren Ihrer Schiffe ueber die Eingabe \'stop\' ins Hauptmenue zurueck." << std::endl;
}

/** Asks the user for a number input which must be between min and max inclusive. */
int Console::number_input(int min, int max) {
    std::string error_message = "Geben Sie eine Ziffer zwischen " + std::to_string(min) + " und " + std::to_string(max) + " ein.";
    while (true) {
        std::string input;
        std::cin >> input;
        if (!is_digits(input)) {
            std::cout << error_message;
            continue;
        }
        int num = std::stoi(input);
        if (num < min || num > max) {
            std::cout << error_message;
            continue;
        }
        return num;
    }
}

bool Console::is_digits(std::string &str) {
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
ship_t Console::ship_input(int size) {
    std::string shipname;
    if (size == 5) {
        shipname = "Schlachtschiffes";
    } else if (size == 4) {
        shipname = "Kreuzers";
    } else if (size == 3) {
        shipname = "Zerstoerers";
    } else {
        shipname = "U-Boots";
    }
    coordinates_t start;
    coordinates_t end;
    while (true) {
        std::cout << "Bitte geben Sie die Startposition ihres " << shipname << " (" << size << ") an: " << std::endl;
        start = coordinateInput(false);
        std::cout << "Bitte geben Sie die Endposition ihres " << shipname << " (" << size << ") an: " << std::endl;
        end = coordinateInput(false);

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
 * Returns {-1, -1} if the user entered stop and stop_allowed is true.
 * Otherwise returns the coordinate.
*/
coordinates_t Console::coordinateInput(bool stop_allowed){
    std::string coordinates;
    int x_value;
    int y_value;
    std::string error_message = "Bitte geben Sie Koordinaten bestehend aus einem Buchstabe von A-J und einer Ziffer von 0-9 an.\n";

    while(true){
        std::cin >> coordinates;
        if(coordinates == "stop" && stop_allowed) {
            return {-1, -1};
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
        return {x_value, y_value};
    }
}

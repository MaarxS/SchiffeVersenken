#include "Field.hpp"
#include "Save.hpp"
#include <iostream>
#include <cmath>

void getPlayerInput(Field &playerfield);
bool checkPlayerInput(Field &playerfield, std::string start_coordinates, std::string end_coordinates, int expected_size);
void playerShot(Field &botfield);

int main() {
    
    Field playerfield;
    Field botfield;
    Save safe;
    safe.loadGame(playerfield, botfield, "Spiel1");

    // playerShot(botfield);
    // safe.saveGame(playerfield, botfield, "Spiel1");
    playerfield.printField(true);
    botfield.printField(true);
    
    // getPlayerInput(playerfield);

}


void getPlayerInput(Field &playerfield){

    std::string coordinates_start;
    std::string coordinates_end;
    bool number_correct = false;

    do{
        std::cout << "Bitte geben Sie die Startposition ihres Schlachtschiffes (5) an: " << std::endl;
        std::cin >> coordinates_start;
        std::cout << "Bitte geben Sie die Endposition ihres Schlachtschiffes (5) an: " << std::endl;
        std::cin >> coordinates_end;

        number_correct = checkPlayerInput(playerfield, coordinates_start, coordinates_end, 5);
    }while(!number_correct);

    for(int i = 0; i < 2; i++){
        do{
            std::cout << "Bitte geben Sie die Startposition ihres " << i + 1 << " .Kreuzers (4) an: " << std::endl;
            std::cin >> coordinates_start;
            std::cout << "Bitte geben Sie die Endposition ihres " << i + 1 << " .Kreuzers (4) an: " << std::endl;
            std::cin >> coordinates_end;

            number_correct = checkPlayerInput(playerfield, coordinates_start, coordinates_end, 4);
        }while(!number_correct);
    }

    for(int i = 0; i < 3; i++){
        do{
            std::cout << "Bitte geben Sie die Startposition ihres " << i + 1 << " .Zerstörers (3) an: " << std::endl;
            std::cin >> coordinates_start;
            std::cout << "Bitte geben Sie die Endposition ihres " << i + 1 << " .Zerstörers (3) an: " << std::endl;
            std::cin >> coordinates_end;

            number_correct = checkPlayerInput(playerfield, coordinates_start, coordinates_end, 4);
        }while(!number_correct);
    }

    for(int i = 0; i < 4; i++){
        do{
            std::cout << "Bitte geben Sie die Startposition ihres " << i + 1 << " .U-Boots (2) an: " << std::endl;
            std::cin >> coordinates_start;
            std::cout << "Bitte geben Sie die Endposition ihres " << i + 1 << " .U-Boots (2) an: " << std::endl;
            std::cin >> coordinates_end;

            number_correct = checkPlayerInput(playerfield, coordinates_start, coordinates_end, 4);
        }while(!number_correct);
    }
}

bool checkPlayerInput(Field &playerfield, std::string start_coordinates, std::string end_coordinates, int expected_size){
    int x_value_start;
    int y_value_start;
    int x_value_end;
    int y_value_end;
    int length_x;
    int length_y;

    if(start_coordinates.length() != 2 || end_coordinates.length() != 2){
          std::cout << "Bitte geben Sie gueltige Koordinaten bestehend aus x und y an. " << std::endl;
          return false;
    }
    if(isdigit(start_coordinates[0])){
        x_value_start = start_coordinates[0] - '0';
        start_coordinates[1] = std::tolower(start_coordinates[1]);
        y_value_start = start_coordinates[1]- 'a';
    }else if(isdigit(start_coordinates[1])){
        x_value_start = start_coordinates[1] - '0';
        start_coordinates[0] = std::tolower(start_coordinates[0]);
        y_value_start = start_coordinates[0] - 'a';
    }else{
         std::cout << "Bitte geben Sie gueltige Startkoordinaten an. " << std::endl;
        return false;
    }

    if(isdigit(end_coordinates[0])){
        x_value_end = end_coordinates[0] - '0';
        end_coordinates[1] = std::tolower(end_coordinates[1]);
        y_value_end = end_coordinates[1]- 'a';
    }else if(isdigit(end_coordinates[1])){
        x_value_end = end_coordinates[1] - '0';
        end_coordinates[0] = std::tolower(end_coordinates[0]);
        y_value_end = end_coordinates[0] - 'a';
    }else{
        std::cout << "Bitte geben Sie gueltige Endkoordinaten an. " << std::endl;
        return false;
    }
    std::cout << x_value_start << std::endl;
    std::cout << x_value_end << std::endl;
    std::cout << y_value_start << std::endl;
    std::cout << y_value_end << std::endl;
    if(x_value_start > 9 || x_value_start < 0 || y_value_start < 0 || y_value_start > 9 || x_value_end > 9 || x_value_end < 0 || y_value_end < 0 || y_value_end > 9 ){
         std::cout << "Bitte geben Sie Koordinaten im gueltigen Zahlenbereich an. " << std::endl;
        return false;
    }

    length_x = abs(x_value_start - x_value_end);
    length_y = abs(y_value_start - y_value_end);

    std::cout << length_x << std::endl;
    std::cout << length_y << std::endl;
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
void playerShot(Field &botfield){
    std::string coordinates;
    bool input_correct = false;
    int x_value;
    int y_value;


    do{
        std::cout << "Bitte geben Sie Ihre Zielkoordinaten an." << std::endl;
        std::cin >> coordinates;

        if(coordinates.length() != 2){
            std::cout << "Bitte geben Sie gueltige Koordinaten bestehend aus x und y an. " << std::endl;
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
            std::cout << "Bitte geben Sie gueltige Zielkoordinaten an. " << std::endl;
            continue;
        }
        if(x_value > 9 || x_value < 0 || y_value > 9 || y_value < 0){
            std::cout << "Bitte geben Sie Koordinaten im gueltigen Zahlenbereich an. " << std::endl;
            continue;
        }
        botfield.shoot(x_value, y_value);
        input_correct = true;

    }while(!input_correct);




}
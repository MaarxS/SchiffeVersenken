#include "Field.hpp"
#include <iostream>
#include <cmath>

void getPlayerInput();
bool checkPlayerInput(std::string start_coordinates, std::string end_coordinates, int expected_size);

int main() {
    
    Field playerfield;
    playerfield.printField(false);
    getPlayerInput();

}


void getPlayerInput(){

    std::string coordinates_start;
    std::string coordinates_end;
    bool number_correct = false;

    do{
        std::cout << "Bitte geben Sie die Startposition ihres Schlachtschiffes (5) an: " << std::endl;
        std::cin >> coordinates_start;
        std::cout << "Bitte geben Sie die Endposition ihres Schlachtschiffes (5) an: " << std::endl;
        std::cin >> coordinates_end;

        number_correct = checkPlayerInput(coordinates_start, coordinates_end, 5);
    }while(!number_correct);

    for(int i = 0; i < 2; i++){
        do{
            std::cout << "Bitte geben Sie die Startposition ihres " << i + 1 << " .Kreuzers (4) an: " << std::endl;
            std::cin >> coordinates_start;
            std::cout << "Bitte geben Sie die Endposition ihres " << i + 1 << " .Kreuzers (4) an: " << std::endl;
            std::cin >> coordinates_end;

            number_correct = checkPlayerInput(coordinates_start, coordinates_end, 4);
        }while(!number_correct);
    }

    for(int i = 0; i < 3; i++){
        do{
            std::cout << "Bitte geben Sie die Startposition ihres " << i + 1 << " .Zerstörers (3) an: " << std::endl;
            std::cin >> coordinates_start;
            std::cout << "Bitte geben Sie die Endposition ihres " << i + 1 << " .Zerstörers (3) an: " << std::endl;
            std::cin >> coordinates_end;

            number_correct = checkPlayerInput(coordinates_start, coordinates_end, 4);
        }while(!number_correct);
    }

    for(int i = 0; i < 4; i++){
        do{
            std::cout << "Bitte geben Sie die Startposition ihres " << i + 1 << " .U-Boots (2) an: " << std::endl;
            std::cin >> coordinates_start;
            std::cout << "Bitte geben Sie die Endposition ihres " << i + 1 << " .U-Boots (2) an: " << std::endl;
            std::cin >> coordinates_end;

            number_correct = checkPlayerInput(coordinates_start, coordinates_end, 4);
        }while(!number_correct);
    }
}

bool checkPlayerInput(std::string start_coordinates, std::string end_coordinates, int expected_size){
    Field playerfield;
    int x_value_start;
    int y_value_start;
    int x_value_end;
    int y_value_end;
    int length_x;
    int length_y;

    if(start_coordinates.length() >= 3 || end_coordinates.length() >= 3){
          std::cout << "Bitte geben Sie gültige Koordinaten bestehend aus x und y an. " << std::endl;
          return false;
    }
    if(isdigit(start_coordinates[0])){
        x_value_start = start_coordinates[0] - '0';
        start_coordinates[1] = std::tolower(start_coordinates[1]);
        y_value_start = start_coordinates[1]- 'a';
    }else{
        x_value_start = start_coordinates[1] - '0';
        start_coordinates[0] = std::tolower(start_coordinates[0]);
        y_value_start = start_coordinates[0] - 'a';
    }

    if(isdigit(end_coordinates[0])){
        x_value_end = end_coordinates[0] - '0';
        end_coordinates[1] = std::tolower(end_coordinates[1]);
        y_value_end = end_coordinates[1]- 'a';
    }else{
        x_value_end = end_coordinates[1] - '0';
        end_coordinates[0] = std::tolower(end_coordinates[0]);
        y_value_end = end_coordinates[0] - 'a';
    }
    std::cout << x_value_start << std::endl;
    std::cout << x_value_end << std::endl;
    std::cout << y_value_start << std::endl;
    std::cout << y_value_end << std::endl;
    if(x_value_start > 9 || x_value_start < 0 || y_value_start < 0 || y_value_start > 9 || x_value_end > 9 || x_value_end < 0 || y_value_end < 0 || y_value_end > 9 ){
         std::cout << "Bitte geben Sie Zahlen im gültigen Zahlenbereich an. " << std::endl;
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
        std::cout << "Bitte achten Sie darauf, dass die Schiffe sich nicht schneiden, berühren oder diagonal platziert werden. " << std::endl;
        return false;
    }

    playerfield.printField(true);
    return true;
}
#include "Field.hpp"
#include <iostream>
#include <cmath>

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
        std::tolower(start_coordinates[1]);
        y_value_start = start_coordinates[1] - 'a';
    }else{
        x_value_start = start_coordinates[1] - '0';
        std::tolower(start_coordinates[0]);
        y_value_start = start_coordinates[0] - 'a';
    }

    if(isdigit(end_coordinates[0])){
        x_value_end = end_coordinates[0] - '0';
        std::tolower(end_coordinates[1]);
        y_value_end = end_coordinates[1] - 'a';
    }else{
        x_value_end = end_coordinates[1] - '0';
        std::tolower(end_coordinates[0]);
        y_value_end = end_coordinates[0] - 'a';
    }

    if(x_value_start > 9 || x_value_start < 0 || y_value_start < 0 || y_value_start > 9 || x_value_end > 9 || x_value_end < 0 || y_value_end < 0 || y_value_end > 9 ){
         std::cout << "Bitte geben Sie eine Zahl im gültigen Zahlenbereich an. " << std::endl;
        return false;
    }
    if(!playerfield.placeShip(x_value_start, x_value_end, y_value_start, y_value_end)){
        std::cout << "Bitte achten Sie darauf, dass die Schiffe sich nicht schneiden, berühren oder diagonal platziert werden. " << std::endl;
        return false;
    }

    length_x = fabs(x_value_start - x_value_end);
    length_y = fabs(y_value_start - y_value_end);

    if(length_x != expected_size && length_y != expected_size){
        std::cout << "Bitte geben Sie ein Schiff der Laenge " << expected_size << " an. "<<std::endl;
        return false;
    }
    //Schiff setzen
    return true;
}
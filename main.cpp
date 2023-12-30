#include "Field.hpp"
#include <iostream>

int main() {
    
    Field playerfield;
    playerfield.printField(false);
    getPlayerInput();
}
void getPlayerInput(){

    Field playerfield;
    std::string coordinates;
    bool numbers_correct = false;

    do{
        std::cout << "Bitte geben Sie die Startposition ihres Schlachtschiffes (5) an: " << std::endl;
        std::cin >> coordinates;
        numbers_correct = checkUserInput(coordinates);
    }while(!numbers_correct);

}
bool checkUserInput(std::string usercoordinates){
    int x_value;
    int y_value;
    if(usercoordinates.length() >= 3){
          std::cout << "Bitte geben Sie gültige Koordinaten bestehend aus x und y an. " << std::endl;
          return false;
    }
    if(isdigit(usercoordinates[0])){
        x_value = usercoordinates[0] - '0';
        std::tolower(usercoordinates[1]);
        y_value = usercoordinates[1] - 'a';
    }else{
        x_value = usercoordinates[1] - '0';
        std::tolower(usercoordinates[0]);
        y_value = usercoordinates[0] - 'a';
    }
    if(x_value > 9 || x_value < 0 || y_value < 0 || x_value > 9){
        
    }
}
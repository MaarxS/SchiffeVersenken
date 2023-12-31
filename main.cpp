#include "Field.hpp"
#include "Computer.hpp"

int main() {
    
    Computer computer;
    computer.placeShips();
    computer.getField()->printField(true);
}
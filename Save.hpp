#pragma once
#include "Field.hpp"
#include <string>

class Save{

    public:
    void saveField(Field &field, std::string filename, std::ofstream &myfile);
    void saveGame(Field &playerfield, Field &botfield, std::string filename);
    void loadGame(Field &playerfield, Field &botfield, std::string filename);
    void loadField(Field &field, std::string filename, std::ifstream &myfile);
};
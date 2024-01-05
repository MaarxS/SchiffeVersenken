#pragma once
#include "Field.hpp"
#include <string>

class Save{

    public:
    void saveField(Field &field, std::string filename, std::ofstream &myfile);
    bool saveGame(Field &playerfield, Field &botfield, std::string filename);
    bool loadGame(Field &playerfield, Field &botfield, std::string filename);
    void loadField(Field &field, std::string filename, std::ifstream &myfile);
};
#pragma once
#include "Field.hpp"
#include <string>
#include <memory>


class Save{

    public:
    void saveField(std::shared_ptr<Field> field, std::string filename, std::ofstream &myfile);
    bool saveGame(std::shared_ptr<Field> playerfield, std::shared_ptr<Field> botfield, std::string filename);
    bool loadGame(std::shared_ptr<Field> playerfield, std::shared_ptr<Field> botfield, std::string filename);
    void loadField(std::shared_ptr<Field> field, std::string filename, std::ifstream &myfile);
};

#pragma once
#include "Field.hpp"
#include <string>
#include <memory>


class Save{
    void saveField(std::shared_ptr<Field> field, std::ofstream &myfile);
    void loadField(std::shared_ptr<Field> field, std::ifstream &myfile);

    public:
    bool saveGame(std::shared_ptr<Field> playerfield, std::shared_ptr<Field> botfield, std::string filename);
    bool loadGame(std::shared_ptr<Field> playerfield, std::shared_ptr<Field> botfield, std::string filename);
};

#include "field.hpp"
#include "Save.hpp"
#include <string>
#include <fstream>
#include <iostream>


bool Save::saveGame(std::shared_ptr<Field> playerfield, std::shared_ptr<Field> botfield, std::string filename){
    filename += ".SVgame";
    std::ofstream myfile;
    myfile.open(filename);
    if(myfile.is_open()){
        saveField(playerfield, filename, myfile);
        saveField(botfield, filename, myfile);
        myfile.close();
        return true;
    }
    return false;   
}

void Save::saveField(std::shared_ptr<Field> field, std::string filename, std::ofstream &myfile){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            bool isShot = field->isShot(j, i);
            bool isShip = field->isShip(j, i);
            if(isShip && isShot){
                 myfile << '3';  //getroffen (3)
            }else if(isShot){
                myfile << '0'; //Schuss ins Meer (0)
            }else if(isShip){
                myfile << '2'; //weiß (plazierte Schiffe) (2)
            }else{
                myfile << '1'; //blau (default Meer) (1)
            }
        }
        myfile << std::endl;
    }
}

bool Save::loadGame(std::shared_ptr<Field> playerfield, std::shared_ptr<Field> botfield, std::string filename){
    if(filename.size() < 7 || filename.substr(filename.size() - 7, filename.size()) != ".SVgame"){
        filename += ".SVgame";
    }
    std::ifstream myfile;
    bool game_over = false;
    myfile.open(filename);
    if(myfile.is_open()){
        playerfield->clear();
        botfield->clear();
        loadField(playerfield, filename, myfile);
        loadField(botfield, filename, myfile);
        myfile.close();
        return true;
    }else{
        return false;
    }    
}

void Save::loadField(std::shared_ptr<Field> field, std::string filename, std::ifstream &myfile){
    int counter = 0;
    std::string line;
    while(getline(myfile,line)){
        for(int j = 0; j < line.length(); j++){
            switch(line[j]){
                case '0': 
                    field->setShot(j, counter);
                    break;
                case '1':
                    break;
                case '2':
                    field->setShip(j, counter);
                    break;
                case '3':
                    field->setShip(j, counter);
                    field->setShot(j, counter);
                    break;
            }
        }
        counter++;
        if(counter == 10){
            return;
        }
    }
}

#include "field.hpp"
#include "Save.hpp"
#include <string>
#include <fstream>
#include <iostream>


bool Save::saveGame(std::shared_ptr<Field> playerField, std::shared_ptr<Field> botField, std::string fileName){
    fileName += ".SVgame";
    std::ofstream myFile;
    myFile.open(fileName);
    if(myFile.is_open()){
        saveField(playerField, fileName, myFile);
        saveField(botField, fileName, myFile);
        myFile.close();
        return true;
    }
    return false;   
}

void Save::saveField(std::shared_ptr<Field> field, std::string fileName, std::ofstream &myFile){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            bool isShot = field->isShot(j, i);
            bool isShip = field->isShip(j, i);
            if(isShip && isShot){
                 myFile << '3';  //getroffen (3)
            }else if(isShot){
                myFile << '0'; //Schuss ins Meer (0)
            }else if(isShip){
                myFile << '2'; //weiß (plazierte Schiffe) (2)
            }else{
                myFile << '1'; //blau (default Meer) (1)
            }
        }
        myFile << std::endl;
    }
}

bool Save::loadGame(std::shared_ptr<Field> playerField, std::shared_ptr<Field> botField, std::string fileName){
    if(fileName.size() < 7 || fileName.substr(fileName.size() - 7, fileName.size()) != ".SVgame"){
        fileName += ".SVgame";
    }
    std::ifstream myFile;
    myFile.open(fileName);
    if(myFile.is_open()){
        playerField->clear();
        botField->clear();
        loadField(playerField, fileName, myFile);
        loadField(botField, fileName, myFile);
        myFile.close();
        return true;
    }else{
        return false;
    }    
}

void Save::loadField(std::shared_ptr<Field> field, std::string fileName, std::ifstream &myFile){
    int counter = 0;
    std::string line;
    while(getline(myFile,line)){
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

#include <iostream>
#include <fstream>
#include <string>
#include "Map.hpp"
#include "Game.hpp"

using string = std::string;
using ifstream = std::ifstream;

void LoadMap(string fileName) {
    //Parse the map file.
    ifstream mapFile(fileName);
    string widthStr, heightStr, jsonFileName;
    int width, height;
    std::getline(mapFile, widthStr, ' ');
    std::getline(mapFile, heightStr, ' ');
    std::getline(mapFile, jsonFileName);

    std::cout << "Map loaded.  JSON file at " << jsonFileName << "\n";
    game = Game(jsonFileName); //Load the game.
}

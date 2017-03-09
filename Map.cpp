#include "GlobalIncludes.hpp"
#include "Map.hpp"
#include "Game.hpp"


void LoadMap(string fileName) {
    //Parse the map file.
    ifstream mapFile(fileName);
    string widthStr, heightStr, jsonFileName;
    int width, height;
    std::getline(mapFile, widthStr, ' ');
    std::getline(mapFile, heightStr, ' ');
    std::getline(mapFile, jsonFileName);
	
    std::cout << "Map loaded("<< widthStr <<","<< heightStr <<").  JSON file at " << jsonFileName << "\n";
    game = Game(jsonFileName); //Load the game.
}

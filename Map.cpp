#include "GlobalIncludes.hpp"
#include <iostream>
#include "Map.hpp"
#include "Game.hpp"
#include "GameDynamicData.hpp"


void LoadMap(string fileName) {
    //Parse the map file.
    ifstream mapFile(fileName);
    string widthStr, heightStr, jsonFileName;
    int width, height;
    std::getline(mapFile, widthStr, ' ');
    std::getline(mapFile, heightStr, ' ');
    std::getline(mapFile, jsonFileName);
	
    std::cout << "Map loaded("<< widthStr <<","<< heightStr <<").  JSON file at " << jsonFileName << "\n";
    game = std::unique_ptr<Game>(new Game(jsonFileName)); //Load the game.

	width = std::stoi(widthStr);
	height = std::stoi(heightStr);
	dynamicData = std::unique_ptr<GameDynamicData>(new GameDynamicData(height, width));
}

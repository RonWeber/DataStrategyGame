#include "GlobalIncludes.hpp"
#include <iostream>
#include "Map.hpp"
#include "Game.hpp"
#include "GameDynamicData.hpp"
#include "LuaManager.hpp"

void gameLoop();

void LoadMap(string fileName) {
    //Parse the map file.
    ifstream mapFile(fileName);
    string widthStr, heightStr, jsonFileName;
    int width, height;
    std::getline(mapFile, widthStr, ' ');
    std::getline(mapFile, heightStr, ' ');
    std::getline(mapFile, jsonFileName);
	
    std::cout << "Map loaded("<< widthStr <<","<< heightStr <<").  JSON file at " << jsonFileName << "\n" << std::endl;

	width = std::stoi(widthStr);
	height = std::stoi(heightStr);

	game = std::unique_ptr<Game>(new Game(jsonFileName, height, width)); //Load the game.

	dynamicData = std::unique_ptr<GameDynamicData>(new GameDynamicData(height, width));

	for(int row = 0; row < height; row++) {
		string line;
		std::getline(mapFile, line);
		if ((int)line.size() < width) {
			throw std::runtime_error("A line in the unit section of the map was not long enough.");
		}
		for (int col = 0; col < width; col++) {
			if (game->unitTypes.count(line[col]) > 0) { //This is a defined unit.
				dynamicData->createUnit(line[col], { col, row });
			}
		}
	}
	string ignoredLine;
	mapFile.ignore(2, '\n');
	for(int row = 0; row < height; row++) {
		string line;
		std::getline(mapFile, line);
		if ((int)line.size() < width) {
			throw std::runtime_error("A line in the terrain section of the map was not long enough.");
		}
		for (int col = 0; col < width; col++) {
			dynamicData->setTerrain(col, row, line[col]);
		}
	}
	dynamicData->startTurn();
	
}


#include <iostream>
#include <fstream>
#include "GlobalIncludes.hpp"
#include "SaveFile.hpp"
#include "Game.hpp"
#include "GameDynamicData.hpp"
#include "Unit.hpp"

void Save(string fileName) {
	json saveFileJson;
	saveFileJson["gameFileName"] = game->fileName;
	saveFileJson["worldHeight"] = game->mapHeight;
	saveFileJson["worldWidth"] = game->mapWidth;	
	//Everything else from Game is part of the file, and will be reloaded when the game is reloaded.  No need to save absolutely everything.

	//TODO: Also save terrain.
	saveFileJson["highestUnitID"] = dynamicData->highestUnitID;

	std::vector<json> unitJsons;
	for (auto unitID : dynamicData->getAllUnits()) {
		Unit& unit = dynamicData->units.at(unitID);
		unitJsons.push_back(unit.toJSON());
	}
	saveFileJson["units"] = unitJsons;

	//Yes, we're storing terrain sideways compared to how it is rendered and diplayed in the map.  So sue me.
	json terrainSection;
	for (auto row : dynamicData->terrain) {
		json rowJson;
		for (auto terrainID : row) {
			string terrainIDString = string(1, (char)terrainID);
			rowJson.push_back(terrainIDString);
		}
		terrainSection.push_back(rowJson);
	}
	saveFileJson["terrain"] = terrainSection;
	std::ofstream saveFile;
	saveFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
	#ifdef PRETTY_SAVE_FILES
	saveFile << std::setw(4) << saveFileJson;
	#else
	saveFile << saveFileJson;
	#endif
	saveFile.close();
}

void LoadSave(string fileName) {
	std::ifstream saveFile;
	saveFile.open(fileName);
	json saveFileJson;
	saveFile >> saveFileJson;

	string gameFileName = saveFileJson["gameFileName"];
	int mapHeight = saveFileJson["worldHeight"];
	int mapWidth = saveFileJson["worldWidth"];
	game = std::unique_ptr<Game>(new Game(gameFileName, mapHeight, mapWidth));
	dynamicData = std::unique_ptr<GameDynamicData>(new GameDynamicData(mapHeight, mapWidth));
	dynamicData->highestUnitID = saveFileJson["highestUnitID"];
	json unitSection = saveFileJson["units"];
	for (auto unitJsonObject : unitSection) {
		Unit u = Unit(unitJsonObject);
		dynamicData->addExistingUnit(u);
	}
	//Yes, we're storing terrain sideways compared to how it is rendered and diplayed in the map.  So sue me.	
	json terrainSection = saveFileJson["terrain"];
	int rowNumber = 0;
	for (auto row : terrainSection) {
		int colNumber = 0;
		for (auto col : row) {
			char terrainID = col.get<string>().at(0);
			dynamicData->terrain[rowNumber][colNumber] = terrainID;
			colNumber++;
		}
		rowNumber++;
	}
}

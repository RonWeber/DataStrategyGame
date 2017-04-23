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
	saveFileJson["highestUnitID"] = game->highestUnitID;
	//Everything else from Game is part of the file, and will be reloaded when the game is reloaded.  No need to save absolutely everything.
	std::vector<json> unitJsons;
	for (auto unitID : dynamicData->getAllUnits()) {
		Unit& unit = dynamicData->units.at(unitID);
		unitJsons.push_back(unit.toJSON());
	}
	saveFileJson["units"] = unitJsons;

	std::ofstream saveFile;
	saveFile.open(fileName);
	saveFile << saveFileJson;
	saveFile.close();
}

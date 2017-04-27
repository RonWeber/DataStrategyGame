#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "LuaManager.hpp"
#include <iostream>

std::unique_ptr<Game> game;
int gridSize;

Game::Game(string globalFileName, int mapHeight, int mapWidth) {
	fileName = globalFileName;
	this->mapHeight = mapHeight;
	this->mapWidth = mapWidth;
	
	//initialize data
	std::ifstream file(globalFileName);
    
	json json;

	file >> json;
	gridSize = json["gridSize"];

	if (json.find("actionIcon") != json.end()) {
		actionIcon = std::shared_ptr<Image>(new Image(json["actionIcon"].get<string>(), false));
	}
	if (json.find("movementIcon") != json.end()) {
		movementIcon = std::shared_ptr<Image>(new Image(json["movementIcon"].get<string>(), false));
	}
	if (json.find("actionIconSeperation") != json.end()) {
		actionIconSeperation = json["actionIconSeperation"];
	} else {
		actionIconSeperation = 8;
	}
	if (json.find("movementIconSeperation") != json.end()) {
		movementIconSeperation = json["movementIconSeperation"];
	} else {
		movementIconSeperation = 8;
	}
	if (json.find("iconOffset") != json.end()) {
		iconOffset = json["iconOffset"];
	}
	else {
		iconOffset = 0;
	}
	if (json.find("hpIcon") != json.end()) {
		hpIcon = std::shared_ptr<Image>(new Image(json["hpIcon"].get<string>(), false));
	}
	if (json.find("hpEmptyIcon") != json.end()) {
		hpEmptyIcon = std::shared_ptr<Image>(new Image(json["hpEmptyIcon"].get<string>(), false));
	}
	

	for (auto file : json["luaFiles"]) {
		lua->loadFile(file);
	}
	for (auto terrain : json["terrainData"]) {
		TerrainType newType = TerrainType(terrain);
		terrainTypes.insert({newType.id, newType});
	}
	for (auto ability : json["abilityData"]) {
		AbilityType newType = AbilityType(ability);
		abilityTypes.insert({ newType.id, newType });
	}
	std::cout << "Abilities loaded.\n" << std::endl;
	for (auto unitType : json["unitData"]) {
		UnitType newType = UnitType(unitType);
		unitTypes.insert({newType.id, newType});
	}
	std::cout << "Units loaded.\n" << std::endl;
}

bool Game::withinBounds(coord pos) {
	return (pos.x >= 0 && pos.x < mapWidth && pos.y >= 0 && pos.y < mapHeight);
}

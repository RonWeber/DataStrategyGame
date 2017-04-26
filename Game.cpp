#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "LuaManager.hpp"
#include <iostream>

std::unique_ptr<Game> game;

Game::Game(string globalFileName, int mapHeight, int mapWidth) {
	fileName = globalFileName;
	this->mapHeight = mapHeight;
	this->mapWidth = mapWidth;
	
	//initialize data
	std::ifstream file(globalFileName);
    
	json json;

	file >> json;
	displayRNG = json["displayRNG"];

	if (json.find("actionIcon") != json.end()) {
		actionIcon = std::shared_ptr<Image>(new Image(json["actionIcon"].get<string>()));
	} 	
	if (json.find("movementIcon") != json.end()) {
		movementIcon = std::shared_ptr<Image>(new Image(json["movementIcon"].get<string>()));
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

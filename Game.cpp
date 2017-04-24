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
	for (auto file : json["luaFiles"]) {
		lua.loadFile(file);
	}
	for (auto terrain : json["terrainData"]) {
		TerrainType newType = TerrainType(terrain);
		terrainTypes.insert({newType.id, newType});
	}
	for (auto ability : json["abilityData"]) {
		AbilityType newType = AbilityType(ability);
		abilityTypes.insert({ newType.id, newType });
	}
	std::cout << "Abilities loaded.\n";
	for (auto unitType : json["unitData"]) {
		UnitType newType = UnitType(unitType);
		unitTypes.insert({newType.id, newType});
	}
	std::cout << "Units loaded.\n";
}

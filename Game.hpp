#pragma once

#include "UnitType.hpp"
#include "AbilityType.hpp"
#include "TerrainType.hpp"
#include "Unit.hpp"
#include "UI.hpp"

class Game {
public:
    Game(string globalFileName, int mapHeight, int mapWidth);
	
    std::map<char, UnitType> unitTypes;
    std::map<string, AbilityType> abilityTypes;
	std::map<TerrainID, TerrainType> terrainTypes;
    bool displayRNG;
    int mapHeight, mapWidth;
	string fileName;
	bool withinBounds(coord pos);

	std::shared_ptr<Image> actionIcon, movementIcon;
	int actionIconSeperation, movementIconSeperation;
private:
};

extern std::unique_ptr<Game> game; //Defined in Game.cpp
//The extern is our low-rent multiple-include guard.

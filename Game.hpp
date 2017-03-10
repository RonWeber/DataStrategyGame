#pragma once

#include "UnitType.hpp"
#include "AbilityType.hpp"
#include "Unit.hpp"
#include "UI.hpp"

class Game {
public:
    Game(string globalFileName);
    std::map<char, UnitType> unitTypes;
    std::map<string, AbilityType> abilityTypes;
    bool displayRNG;
    int mapHeight, mapWidth;
	unitID highestUnitID = 0;
private:
};

extern std::unique_ptr<Game> game; //Defined in Game.cpp
//The extern is our low-rent multiple-include guard.

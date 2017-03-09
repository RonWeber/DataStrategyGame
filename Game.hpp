#pragma once

#include "UnitType.hpp"
#include "AbilityType.hpp"

class Game {
public:
    Game();
    Game(string globalFileName);
    std::map<char, UnitType> unitTypes;
    std::map<string, AbilityType> abilityTypes;
    bool displayRNG;
private:
	void draw_grid();
	int gridX, gridY;
	enum selectionType { none = 0, unit, ability };
	selectionType selectionLevel; //0 = top, 1 = unit selected, 2 = ability selected
	int unitSelected = 0;
	string abilitySelected = "";
};

extern Game game; //Defined in Game.cpp
//The extern is our low-rent multiple-include guard.
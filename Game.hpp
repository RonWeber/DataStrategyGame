#pragma once
#include "UnitType.hpp"
#include "AbilityType.hpp"
#include <string>

using string = std::string;

class Game {
public:
    Game();
    Game(string globalFileName);
    std::map<char, UnitType> unitTypes;
    std::map<string, AbilityType> abilityTypes;
    bool displayRNG;
};

extern Game game; //Defined in Game.cpp
//The extern is our low-rent multiple-include guard.

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
};

extern Game game; //Defined in Game.cpp
//The extern is our low-rent multiple-include guard.
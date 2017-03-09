#pragma once
#include "UnitType.hpp"
#include "AbilityType.hpp"
#include <string>

using string = std::string;

class Game {
public:
    Game(string globalFileName);
    std::map<char, UnitType> unitTypes;
    std::map<string, AbilityType> abilityTypes;
};

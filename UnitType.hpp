#pragma once

#include "AbilityType.hpp"
#include "Unit.hpp"
#include "Image.hpp"


class UnitType {
public:
    UnitType(json jsonSection);

    char id;
    Image image;
    int maxHP, movesPerTurn, actionsPerTurn;
    std::map<string, string> extraData;
    std::vector<AbilityType> abilities;
    string name;
    string description;

    Unit makeUnit();
};

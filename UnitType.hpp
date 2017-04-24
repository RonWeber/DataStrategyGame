#pragma once

#include "AbilityType.hpp"
#include "Unit.hpp"
#include "Image.hpp"
#include "GameDynamicData.hpp"

class UnitType {
public:
    UnitType(json jsonSection);

    char id;
	std::shared_ptr<Image> image;
    int maxHP, movesPerTurn, actionsPerTurn;
    std::map<string, int> extraData;
    std::vector<string> abilities;
    string name;
    string description;
	sideID side;

    Unit makeUnit(coord initialCoord);
};

#pragma once
#include "GlobalIncludes.hpp"

typedef int unitID;
const unitID NO_UNIT = -1;

class Unit {
public:
	Unit(unitID id, std::map<string, int> data_keys,
		 coord coordinate, char unitTypeID, std::vector<string> abilities, sideID side);
	Unit(json saveFileSection);
	unitID id;
	std::map<string, int> data_keys;
	coord coordinate;
    char unitTypeID;
    std::vector<string> abilities;
	sideID owner;
	int hp, movesRemaining, actionsRemaining;
	
    json toJSON();
};

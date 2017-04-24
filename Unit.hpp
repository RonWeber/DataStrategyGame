#pragma once

typedef int unitID;
const unitID NO_UNIT = -1;

class Unit {
public:
	Unit(unitID id, std::map<string, int> data_keys,
		 coord coordinate, char unitTypeID, std::vector<string> abilities);
	Unit(json saveFileSection);
	unitID id;
	std::map<string, int> data_keys;
	coord coordinate;
    char unitTypeID;
    std::vector<string> abilities;
	
    json toJSON();
};

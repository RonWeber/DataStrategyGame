#pragma once

typedef int unitID;

class Unit {
public:
    unitID id;
    std::map<string, int> data_keys;
	coord coordinate;
    char unitTypeID;
    std::vector<string> abilities;

    json toJSON();
};

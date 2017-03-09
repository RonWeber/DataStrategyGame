#pragma once

typedef int unitID;

class Unit {
public:
    unitID id;
    std::map<string, int> data_keys;
    char unitTypeID;
    std::vector<string> abilities;

    json toJSON();
};

#pragma once

class Unit {
public:
    int id;
    std::map<string, int> data_keys;
    char unitTypeID;
    std::vector<string> abilities;

    json toJSON();
};

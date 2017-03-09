#pragma once

#include "Unit.hpp"

typedef char TerrainID;

class GameDynamicData {
public:
    std::map<unitID, Unit> units;
    std::vector<std::vector<TerrainID>> terrain;

    int getValue(unitID unitID, string key);
    void setValue(unitID unitID, string key, int newValue);
    void addAbility(unitID unitID, string abilityType);
    void removeAbility(unitID unitID, string abilityType);
    unitID createUnit(char unitType, int x, int y);
    TerrainID getTerrain(int x, int y);
    std::vector<unitID> getAllUnits();

    json toJson();
};

extern GameDynamicData dynamicData;

#pragma once

#include "Unit.hpp"
#include "GlobalIncludes.hpp"

class GameDynamicData {
public:
	GameDynamicData(int height, int width);
    std::map<unitID, Unit> units;
	std::vector<std::vector<TerrainID>> terrain;	
	unitID highestUnitID = 0;
	sideID currentPlayer = 0;

    int getValue(unitID unitID, string key);
    void setValue(unitID unitID, string key, int newValue);
	int getOwner(unitID unitID);
	void setPos(unitID unitID, coord newPos);
	coord getPos(unitID unitID);
    void addAbility(unitID unitID, string abilityType);
    void removeAbility(unitID unitID, string abilityType);
    unitID createUnit(char unitType, coord coord);
	void deleteUnit(unitID id);
	void addExistingUnit(Unit u);
	
	void setTerrain(int x, int y, char terrainType);
    TerrainID getTerrain(int x, int y);
	std::vector<unitID> getAllUnits();
	unitID unitAt(coord coord);

	void startTurn();
	void update();
	void endTurn();

    json toJson();
private:
	std::vector<std::vector<unitID>> positions;

};

extern std::unique_ptr<GameDynamicData> dynamicData;

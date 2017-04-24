#include "GlobalIncludes.hpp"
#include "GameDynamicData.hpp"
#include "Game.hpp"

std::unique_ptr<GameDynamicData> dynamicData;

GameDynamicData::GameDynamicData(int height, int width) {
	positions.resize(width);
	terrain.resize(width);
	for(int x = 0; x < width; x++) {
		positions[x].resize(height, NO_UNIT);
		terrain[x].resize(height, '\0');
	}
}

int GameDynamicData::getValue(unitID unitID, string key) {
	return units.at(unitID).data_keys[key];
}

void GameDynamicData::setValue(unitID unitID, string key, int newValue) {
	Unit u = units.at(unitID);
	u.data_keys[key] = newValue;
}

void GameDynamicData::setPos(unitID unitID, coord newPos) {
	Unit u = units.at(unitID);
	positions[u.coordinate.x][u.coordinate.y] = NO_UNIT;
	u.coordinate = newPos;
	positions[u.coordinate.x][u.coordinate.y] = u.id;
}

coord GameDynamicData::getPos(unitID unitID) {
	return units.at(unitID).coordinate;
}

void GameDynamicData::addAbility(unitID unitID, string abilityType) {
	units.at(unitID).abilities.push_back(abilityType);
}

void GameDynamicData::removeAbility(unitID unitID, string abilityType) {
	Unit* unit = &units.at(unitID);
	auto abilityIt = std::find(unit->abilities.begin(), unit->abilities.end(), abilityType);
	unit->abilities.erase(abilityIt);
}

int GameDynamicData::createUnit(char unitType, coord coord) {
	Unit u = game->unitTypes.at(unitType).makeUnit(coord);
	addExistingUnit(u);
	return u.id;
}

void GameDynamicData::addExistingUnit(Unit u) {
	units.insert({u.id, u});
	positions[u.coordinate.x][u.coordinate.y] = u.id;
}

void GameDynamicData::setTerrain(int x, int y, char terrainType) {
	terrain[x][y] = terrainType;
}

TerrainID GameDynamicData::getTerrain(int x, int y) {
	return terrain[x][y];
}

std::vector<unitID> GameDynamicData::getAllUnits() {
	std::vector<unitID> result;
	for (auto pair : units) {
		result.push_back(pair.first);
	}
	return result;
}


unitID GameDynamicData::unitAt(coord coord) {
	return positions[coord.x][coord.y];
}

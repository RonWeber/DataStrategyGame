#include "GlobalIncludes.hpp"
#include "GameDynamicData.hpp"
#include "Game.hpp"

std::unique_ptr<GameDynamicData> dynamicData;


GameDynamicData::GameDynamicData(int height, int width) {
	positions.resize(width);
	for(int x = 0; x < width; x++) {
		positions[x].resize(height, NO_UNIT);
	}
}

int GameDynamicData::getValue(unitID unitID, string key) {
	return units[unitID].data_keys[key];
}

void GameDynamicData::setValue(unitID unitID, string key, int newValue) {
	Unit u = units[unitID];
	u.data_keys[key] = newValue;
	units[unitID] = u;
}

void GameDynamicData::setPos(unitID unitID, coord newPos) {
	Unit u = units[unitID];
	positions[u.coordinate.x][u.coordinate.y] = NO_UNIT;
	u.coordinate = newPos;
	positions[u.coordinate.x][u.coordinate.y] = u.id;
	units[unitID] = u;
}

coord GameDynamicData::getPos(unitID unitID) {
	return units[unitID].coordinate;
}

void GameDynamicData::addAbility(unitID unitID, string abilityType) {
	units[unitID].abilities.push_back(abilityType);
}

void GameDynamicData::removeAbility(unitID unitID, string abilityType) {
	Unit* unit = &units[unitID];
	auto abilityIt = std::find(unit->abilities.begin(), unit->abilities.end(), abilityType);
	unit->abilities.erase(abilityIt);
}

int GameDynamicData::createUnit(char unitType, coord coord) {
	Unit u = game->unitTypes.at(unitType).makeUnit(coord);
	units.insert({u.id, u});
	positions[u.coordinate.x][u.coordinate.y] = u.id;
	return u.id;
}

TerrainID GameDynamicData::getTerrain(int x, int y) {
	return '\0';
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

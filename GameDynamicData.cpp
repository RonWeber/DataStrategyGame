#include "GlobalIncludes.hpp"
#include "GameDynamicData.hpp"
#include "Game.hpp"

GameDynamicData dynamicData;

int GameDynamicData::getValue(unitID unitID, string key) {
	return units[unitID].data_keys[key];
}

void GameDynamicData::setValue(unitID unitID, string key, int newValue) {
	units[unitID].data_keys[key] = newValue;
}

void GameDynamicData::addAbility(unitID unitID, string abilityType) {
	units[unitID].abilities.push_back(abilityType);
}

void GameDynamicData::removeAbility(unitID unitID, string abilityType) {
	Unit* unit = &units[unitID];
	auto abilityIt = std::find(unit->abilities.begin(), unit->abilities.end(), abilityType);
	unit->abilities.erase(abilityIt);
}

int GameDynamicData::createUnit(char unitType, int x, int y) {
	Unit u = game->unitTypes.at(unitType).makeUnit();
	units.insert({u.id, u});
	return u.id;
}

TerrainID GameDynamicData::getTerrain(int x, int y) {
}

std::vector<unitID> GameDynamicData::getAllUnits() {
	std::vector<unitID> result;
	for (auto pair : units) {
		result.push_back(pair.first);
	}
	return result;
}

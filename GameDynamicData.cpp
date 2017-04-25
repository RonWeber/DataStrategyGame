#include "GlobalIncludes.hpp"
#include "GameDynamicData.hpp"
#include "Game.hpp"
#include "LuaManager.hpp"

std::unique_ptr<GameDynamicData> dynamicData;

GameDynamicData::GameDynamicData(int height, int width) {
	positions.resize(width);
	terrain.resize(width);
	for (int x = 0; x < width; x++) {
		positions[x].resize(height, NO_UNIT);
		terrain[x].resize(height, '\0');
	}
}

int GameDynamicData::getValue(unitID unitID, string key) {
	return units.at(unitID).data_keys[key];
}
int GameDynamicData::getOwner(unitID unitID) {
	return units.at(unitID).owner;
}


void GameDynamicData::setValue(unitID unitID, string key, int newValue) {
	Unit &u = units.at(unitID);
	u.data_keys[key] = newValue;
}

void GameDynamicData::setPos(unitID unitID, coord newPos) {
	if (positions[newPos.x][newPos.y] != NO_UNIT){
		setValue(positions[newPos.x][newPos.y], "hp", 0);
	}
	Unit &u = units.at(unitID);
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

void GameDynamicData::deleteUnit(unitID id) {
	Unit &deadManWalking = units.at(id);
	if (positions[deadManWalking.coordinate.x][deadManWalking.coordinate.y] == id)
		positions[deadManWalking.coordinate.x][deadManWalking.coordinate.y] = NO_UNIT;
	units.erase(id);
}

void GameDynamicData::addExistingUnit(Unit u) {
	units.insert({u.id, u});
	positions[u.coordinate.x][u.coordinate.y] = u.id;
}

void GameDynamicData::setTerrain(int x, int y, char terrainType) {
	if (game->withinBounds({ x, y })) {
		terrain[x][y] = terrainType;
	}
}

TerrainID GameDynamicData::getTerrain(int x, int y) {
	if (game->withinBounds({ x, y })) {
		return terrain[x][y];
	}
	else return NO_UNIT;//not a unit, but this shouldn't happen anyway
}

std::vector<unitID> GameDynamicData::getAllUnits() {
	std::vector<unitID> result;
	for (auto pair : units) {
		result.push_back(pair.first);
	}
	return result;
}

unitID GameDynamicData::unitAt(coord coord) {
	if (game->withinBounds(coord)) {
		return positions[coord.x][coord.y];
	}
	else return NO_UNIT;
}

void GameDynamicData::startTurn() {
	for (auto unit : this->getAllUnits()) {
		Unit &u = units.at(unit);		
		for (auto ability : u.abilities) {
			AbilityType &type =  game->abilityTypes.at(ability);
			if (type.functionNames.count(LuaFunction::TurnStart) > 0) {
				lua->CallFunction(type.functionNames.at(LuaFunction::TurnStart), unit);
			}
		}
	}
}

void GameDynamicData::endTurn() {
	//TODO: All kinds of exciting end turn stuff.
	for (auto unit : this->getAllUnits()) {
		Unit &u = units.at(unit);
		for (auto ability : u.abilities) {
			AbilityType &type = game->abilityTypes.at(ability);
			if (type.functionNames.count(LuaFunction::TurnEnd) > 0) {
				lua->CallFunction(type.functionNames.at(LuaFunction::TurnEnd), unit);
			}
		}
	}

	currentPlayer = (currentPlayer == 0) ? 1 : 0;
	startTurn(); //The next turn.
}

void GameDynamicData::update() {
	bool anydead;
	do {
		anydead = false;
		for (auto unit : this->getAllUnits()) {
			Unit &u = units.at(unit);
			bool deadThisTurn = getValue(u.id, "hp") <= 0;
			for (auto ability : u.abilities) {
				AbilityType &type = game->abilityTypes.at(ability);
				if (deadThisTurn && type.functionNames.count(LuaFunction::UnitDied) > 0) {
					lua->CallFunction(type.functionNames.at(LuaFunction::UnitDied), unit);
				}
			}
			if (deadThisTurn) {
				deleteUnit(unit);
				anydead = true;
			}
		}
	} while (anydead);
}
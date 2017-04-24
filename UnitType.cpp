#include "GlobalIncludes.hpp"
#include "UnitType.hpp"
#include "Game.hpp"
#include "GameDynamicData.hpp"

UnitType::UnitType(json jsonSection) {
	id = jsonSection["id"].get<string>().at(0);
	side = jsonSection["side"];
	image = std::shared_ptr<Image>(new Image(jsonSection["Image"].get<string>()));
	maxHP = jsonSection["maxHP"];
	movesPerTurn = jsonSection["maxMoves"];
	actionsPerTurn = jsonSection["maxAP"];
	json extraDataJson = jsonSection["extraData"];
	for (json::iterator it = extraDataJson.begin(); it != extraDataJson.end(); ++it) {
		extraData.insert({it.key(), it.value().get<int>()});
	}
	for (auto json : jsonSection["abilities"]) {
		abilities.push_back(json.get<string>());
	}
	name = jsonSection["name"];
	description = jsonSection["description"];
}



Unit UnitType::makeUnit(coord initialCoord) {
	Unit result = Unit(++dynamicData->highestUnitID, extraData, initialCoord, id, abilities);
	return result;
}

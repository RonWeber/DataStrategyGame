#include "GlobalIncludes.hpp"
#include "UnitType.hpp"
#include "Game.hpp"

UnitType::UnitType(json jsonSection) {
	id = jsonSection["id"].get<string>().at(0);
	side = jsonSection["side"];
	image = std::shared_ptr<Image>(new Image(jsonSection["Image"].get<string>()));
	maxHP = jsonSection["maxHP"];
	movesPerTurn = jsonSection["maxMoves"];
	actionsPerTurn = jsonSection["maxAP"];
	for (auto json : jsonSection["extraData"]) {
		extraData.insert({jsonSection["key"].get<string>(), jsonSection["value"].get<int>()});
	}
	for (auto json : jsonSection["abilities"]) {
		abilities.push_back(json.get<string>());
	}
	name = jsonSection["name"];
	description = jsonSection["description"];
}



Unit UnitType::makeUnit() {
	Unit result = Unit();
	result.id = ++game->highestUnitID;
	result.unitTypeID = id;
	result.data_keys = extraData;
	result.abilities = abilities;
}

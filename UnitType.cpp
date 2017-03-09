#include "GlobalIncludes.hpp"
#include "UnitType.hpp"

UnitType::UnitType(json jsonSection) {
	id = jsonSection["id"].get<string>().at(0);
	side = jsonSection["side"];
	image = Image(jsonSection["Image"].get<string>());
	maxHP = jsonSection["maxHP"];
	movesPerTurn = jsonSection["maxMoves"];
	actionsPerTurn = jsonSection["maxAP"];
	for (auto json : jsonSection["extraData"]) {
		extraData.insert({jsonSection["key"].get<string>(), jsonSection["value"].get<string>()});
	}
	for (auto json : jsonSection["abilities"]) {
		abilities.push_back(json.get<string>());
	}
	name = jsonSection["name"];
	description = jsonSection["description"];
}

Unit UnitType::makeUnit() {
}

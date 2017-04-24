#include "GlobalIncludes.hpp"
#include "Unit.hpp"

Unit::Unit(unitID id, std::map<string, int> data_keys, coord coordinate,
		   char unitTypeID, std::vector<string> abilities) {
	this->id = id;
	this->data_keys = data_keys;
	this->coordinate = coordinate;
	this->unitTypeID = unitTypeID;
	this->abilities = abilities;
}

/**
   The fromJson constructor.
**/
Unit::Unit(json saveFileSection) {
	//This is the opposite of toJSON
	this->id = saveFileSection["id"];
	json dataJson = saveFileSection["data"];
	for (json::iterator it = dataJson.begin(); it != dataJson.end(); ++it) {
		data_keys.insert({it.key(), it.value().get<int>()});
	}
	json coordinateJson = saveFileSection["coordinate"];
	this->coordinate = {coordinateJson["x"], coordinateJson["y"]};
	string typeString = saveFileSection["type"];
	this->unitTypeID = typeString.at(0);
	for (auto ability : saveFileSection["abilities"]) {
		abilities.push_back(ability);
	}
}

json Unit::toJSON() {
	json result;
	result["id"] = id;
	json data;
	for (auto const& entry : data_keys) {
		data[entry.first] = entry.second;
	}
	result["data"] = data;
	json coordinateJson;
	coordinateJson["x"] = coordinate.x;
	coordinateJson["y"] = coordinate.y;
	result["coordinate"] = coordinateJson;
	string typeString = string(1, unitTypeID);
	result["type"] = typeString;
	result["abilities"] = abilities;
	return result;
}

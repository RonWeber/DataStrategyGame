#include "GlobalIncludes.hpp"
#include "Unit.hpp"

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
	result["type"] = unitTypeID;
	result["abilities"] = abilities;
	return result;
}

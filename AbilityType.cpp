#include <iostream>
#include "GlobalIncludes.hpp"
#include "AbilityType.hpp"


bool existsInJson(json jsonSection, string key) {
	return jsonSection.find(key) != jsonSection.end();
}

void AbilityType::conditionalAdd(json jsonSection, LuaFunction function, string jsonName) {
	
    if (existsInJson(jsonSection, jsonName)) {
		functionNames.insert({function, jsonSection[jsonName].get<string>()});
	} 
}

AbilityType::AbilityType(json json) {
	id = json["id"];
	Name = json["description"];
	selectionAbility = json["selection"];
	image = std::shared_ptr<Image>(new Image(json["Image"].get<string>()));
	conditionalAdd(json, Available, "availableFn");
	conditionalAdd(json, Action, "actionFn");
	conditionalAdd(json, AllowedLocations, "allowedLocationsFn");
	conditionalAdd(json, HelperData, "helperDataFn");	
	conditionalAdd(json, UnitCreated, "unitCreatedFn");
	conditionalAdd(json, UnitDied, "unitDiedFn");
	conditionalAdd(json, TurnStart, "turnStartFn");
	conditionalAdd(json, TurnEnd, "turnEndFn");
}


void AbilityType::useAbility(LuaFunction ability) {
}

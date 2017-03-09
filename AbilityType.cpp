#include "GlobalIncludes.hpp"
#include "AbilityType.hpp"

AbilityType::AbilityType(json jsonSection) {
    bool exists = jsonSection.find("turnStartFn") != jsonSection.end();
    if (exists) {
	json turnStartFnJson = jsonSection.at("turnStartFn");
	functionNames.insert({TurnStart, turnStartFnJson.get<string>()});
    }
}

void AbilityType::useAbility(LuaFunction ability) {
}

#pragma once
#include "Image.hpp"

enum LuaFunction { Available, Action, AllowedLocations, HelperData, UnitCreated, UnitDied, TurnStart, TurnEnd };

class AbilityType {
public:
    AbilityType(json jsonSection);

    string id;
    string Name;
    bool selectionAbility;
    std::map<LuaFunction, string> functionNames;
	std::shared_ptr<Image> image;

    void useAbility(LuaFunction ability);
private:
	void conditionalAdd(json jsonSection, LuaFunction function, string jsonName);
};

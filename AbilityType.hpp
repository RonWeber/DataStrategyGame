#include "json.hpp"

using json = nlohmann::json;
using string = std::string;

Enum LuaFunction { Available, Action, AllowedLocations, HelperData, UnitCreated, UnitDied, TurnStart, TurnEnd };

class AbilityType {
public:
    AbilityType(json jsonSection);

    string id;
    string Name;
    bool selectionAbility;
    std::map<LuaFunction, string> functionNames;

    void useAbility(LuaFunction ability);
};

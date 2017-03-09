#include "json.hpp"
#include "AbilityType.hpp"
#include <string>

using json = nlohmann::json;
using string = std::string;

class UnitType {
public:
    UnitType(json jsonSection);

    char id;
    Image image;
    int maxHP, movesPerTurn, actionsPerTurn;
    std::map<string, string> extraData;
    std::vector<AbilityType> abilities;
    string name;
    string description;
    Image image;

    Unit makeUnit();
};

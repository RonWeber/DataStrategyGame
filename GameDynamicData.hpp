#include "Unit.hpp"
#include "json.hpp"

using json = nlohmann::json;
using string=std::string;
typedef char TerrainID;

std::map<int, Unit> units;
std::vector<std::vector<TerrainID>> terrain;

int getValue(int unitID, string key);
void setValue(int unitID, string key, int newValue);
void addAbility(int unitID, string abilityType);
void removeAbility(int unitID, string abilityType);
int createUnit(char unitType, int x, int y);
TerrainID getTerrain(int x, int y);
std::vector<int> getAllUnits();

json toJson();

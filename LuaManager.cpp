#include "GlobalIncludes.hpp"
#include "LuaManager.hpp"
#include "GameDynamicData.hpp"
#include "Game.hpp"

std::unique_ptr<LuaManager> lua;

//Functions lua code calls
static int getValue(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -2);
	const char* key = lua_tostring(L, -1);
	lua_pushinteger(L, dynamicData->getValue(unitID, key));
	return 1;
}
static int getOwner(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -1);
	lua_pushinteger(L, dynamicData->getOwner(unitID));
	return 1;
}

static int setValue(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -3);
	const char* key = lua_tostring(L, -2);
	int value = (int)lua_tointeger(L, -1);
	dynamicData->setValue(unitID, key, value);
	return 0;
}

static int addValue(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -3);
	const char* key = lua_tostring(L, -2);
	int value = (int)lua_tointeger(L, -1);
	dynamicData->setValue(unitID, key, dynamicData->getValue(unitID, key)+value);
	return 0;
}

static int getPos(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -1);
	coord tmp = dynamicData->getPos(unitID);
	lua_pushinteger(L, tmp.x);
	lua_pushinteger(L, tmp.y);
	return 2;
}

static int setPos(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -3);
	int x = (int)lua_tointeger(L, -2);
	int y = (int)lua_tointeger(L, -1);
	dynamicData->setPos(unitID, { x, y });
	return 0;
}
static int addAbility(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -2);
	const char* ability = lua_tostring(L, -1);
	dynamicData->addAbility(unitID, ability);
	return 0;
}
static int hasAbility(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -2);
	const char* ability = lua_tostring(L, -1);
	lua_pushboolean(L, dynamicData->hasAbility(unitID, ability));
	return 1;
}
static int removeAbility(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -2);
	const char* ability = lua_tostring(L, -1);
	dynamicData->removeAbility(unitID, ability);
	return 0;
}
static int createUnit(lua_State *L) {
	int unitType = lua_tostring(L, -3)[0];
	int x = (int)lua_tointeger(L, -2);
	int y = (int)lua_tointeger(L, -1);
	lua_pushinteger(L, dynamicData->createUnit(unitType, { x, y }));
	return 1;
}
static int unitAt(lua_State *L) {
	int x = (int)lua_tointeger(L, -2);
	int y = (int)lua_tointeger(L, -1);
	lua_pushinteger(L, dynamicData->unitAt({ x, y }));
	return 1;
}
static int withinBounds(lua_State *L) {
	int x = (int)lua_tointeger(L, -2);
	int y = (int)lua_tointeger(L, -1);
	lua_pushboolean(L, game->withinBounds({ x, y }));
	return 1;
}
static int getAllUnits(lua_State *L) {
	auto list = dynamicData->getAllUnits();
	lua_createtable(L,list.size(),0);
	int i = 0;
	for (auto u : list) {
		i++;
		lua_pushnumber(L, i);
		lua_pushnumber(L, u);
		lua_settable(L, -3);
	}
	return 1;
}
static int getTerrain(lua_State *L) {
	int x = (int)lua_tointeger(L, -2);
	int y = (int)lua_tointeger(L, -1);
	const char t = dynamicData->getTerrain( x, y );
	const char str[2] = { t, '\0' };
	lua_pushstring(L, str);
	return 1;
}

//To be implemented
//TerrainID getTerrain(int x, int y);
//std::vector<unitID> getAllUnits();


//LuaManager itself
LuaManager::LuaManager() {
	L = luaL_newstate();

	luaL_openlibs(L);

	lua_pushcfunction(L, getValue);
	lua_setglobal(L, "getValue");
	lua_pushcfunction(L, getOwner);
	lua_setglobal(L, "getOwner");
	lua_pushcfunction(L, setValue);
	lua_setglobal(L, "setValue");
	lua_pushcfunction(L, addValue);
	lua_setglobal(L, "addValue");

	lua_pushcfunction(L, getPos);
	lua_setglobal(L, "getPos");
	lua_pushcfunction(L, setPos);
	lua_setglobal(L, "setPos");

	lua_pushcfunction(L, addAbility);
	lua_setglobal(L, "addAbility");
	lua_pushcfunction(L, hasAbility);
	lua_setglobal(L, "hasAbility");
	lua_pushcfunction(L, removeAbility);
	lua_setglobal(L, "removeAbility");

	lua_pushcfunction(L, createUnit);
	lua_setglobal(L, "createUnit");
	lua_pushcfunction(L, unitAt);
	lua_setglobal(L, "unitAt");

	lua_pushcfunction(L, withinBounds);
	lua_setglobal(L, "withinBounds");
	lua_pushcfunction(L, getAllUnits);
	lua_setglobal(L, "getAllUnits");

	lua_pushcfunction(L, getTerrain);
	lua_setglobal(L, "getTerrain");

	lua_pushinteger(L, NO_UNIT);
	lua_setglobal(L, "NO_UNIT");
}

void LuaManager::loadFile(string filename) {
	//load the library file then execute it to register the functions
	if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
	{
		std::cerr << "cannot run configuration file: %s" << lua_tostring(L, -1) << std::endl;
		//Throw?
	}
}

void LuaManager::CallFunction(string fn, unitID unit) {
	lua_getglobal(L, fn.c_str());
	lua_pushinteger(L, unit);
	if (lua_pcall(L, 1, 0, 0) != 0) {
		std::cerr << "error running function " << fn << ": " << lua_tostring(L, -1) << std::endl;
		//Throw?
	}
}
void LuaManager::CallFunction(string fn, unitID unit, coord pos) {
	lua_getglobal(L, fn.c_str());
	lua_pushinteger(L, unit);
	lua_pushinteger(L, pos.x);
	lua_pushinteger(L, pos.y);
	if (lua_pcall(L, 3, 0, 0) != 0){
		std::cerr << "error running function " << fn << ": " << lua_tostring(L, -1) << std::endl;
		//Throw?
	}
}

bool LuaManager::CallFunctionAvailable(string fn, unitID unit) {
	lua_getglobal(L, fn.c_str());
	lua_pushinteger(L, unit);
	if (lua_pcall(L, 1, 1, 0) != 0){
		std::cerr << "error running function " << fn << ": " << lua_tostring(L, -1) << std::endl;
		//Throw?
	}
	lua_isboolean(L, -1);
	bool result = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return result;
}

std::unique_ptr<std::unordered_set<coord>> LuaManager::CallFunctionAllowedLocations(string fn, unitID unit) {
	lua_getglobal(L, fn.c_str());
	lua_pushinteger(L, unit);
	if (lua_pcall(L, 1, 1, 0) != 0) {
		std::cerr << "error running function " << fn << ": " << lua_tostring(L, -1) << std::endl;
		//Throw?
	}
	auto vals = std::unique_ptr<std::unordered_set<coord>>(new std::unordered_set<coord>);
	lua_istable(L, 0);
	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		lua_isnumber(L, -1);
		int x = lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_next(L, -2);
		lua_isnumber(L, -1);
		int y = lua_tonumber(L, -1);
		lua_pop(L, 1);
		if (game->withinBounds({ x, y }))
			vals->insert({ x, y });
	}

	lua_pop(L, 1);
	return vals;
}

LuaManager::~LuaManager() {
	lua_close(L);
}

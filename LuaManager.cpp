#include "GlobalIncludes.hpp"
#include "LuaManager.hpp"
#include "GameDynamicData.hpp"

LuaManager lua;

//Functions lua code calls
static int getValue(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -1);
	const char* key = lua_tostring(L, -2);
	lua_pushinteger(L, dynamicData->getValue(unitID, key));
	return 1;
}

static int setValue(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -1);
	const char* key = lua_tostring(L, -2);
	int value = (int)lua_tointeger(L, -3);
	dynamicData->setValue(unitID, key, value);
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
	int unitID = (int)lua_tointeger(L, -1);
	int x = (int)lua_tointeger(L, -2);
	int y = (int)lua_tointeger(L, -3);
	dynamicData->setPos(unitID, { x, y });
	return 0;
}
static int addAbility(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -1);
	const char* ability = lua_tostring(L, -2);
	dynamicData->addAbility(unitID, ability);
	return 0;
}
static int removeAbility(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -1);
	const char* ability = lua_tostring(L, -2);
	dynamicData->removeAbility(unitID, ability);
	return 0;
}
static int createUnit(lua_State *L) {
	int unitType = lua_tostring(L, -1)[0];
	int x = (int)lua_tointeger(L, -2);
	int y = (int)lua_tointeger(L, -3);
	lua_pushinteger(L, dynamicData->createUnit(unitType, { x, y }));
	return 1;
}
static int unitAt(lua_State *L) {
	int x = (int)lua_tointeger(L, -1);
	int y = (int)lua_tointeger(L, -2);
	lua_pushinteger(L, dynamicData->unitAt({ x, y }));
	return 1;
}

//To be implemented
//TerrainID getTerrain(int x, int y);
//std::vector<unitID> getAllUnits();


//LuaManager itself
LuaManager::LuaManager() {
	L = luaL_newstate();

	lua_pushcfunction(L, getValue);
	lua_setglobal(L, "getValue");
	lua_pushcfunction(L, setValue);
	lua_setglobal(L, "setValue");

	lua_pushcfunction(L, getPos);
	lua_setglobal(L, "getPos");
	lua_pushcfunction(L, setPos);
	lua_setglobal(L, "setPos");

	lua_pushcfunction(L, addAbility);
	lua_setglobal(L, "addAbility");
	lua_pushcfunction(L, removeAbility);
	lua_setglobal(L, "removeAbility");

	lua_pushcfunction(L, createUnit);
	lua_setglobal(L, "createUnit");
	lua_pushcfunction(L, unitAt);
	lua_setglobal(L, "unitAt");
}

void LuaManager::loadFile(string filename) {
	luaL_loadfile(L, filename.c_str());
}

void LuaManager::CallFunction(string fn, unitID unit) {
	lua_getglobal(L, fn.c_str());
	lua_pushinteger(L, unit);
	lua_call(L, 1, 0);
}
void LuaManager::CallFunction(string fn, unitID unit, coord pos) {
	lua_getglobal(L, fn.c_str());
	lua_pushinteger(L, unit);
	lua_pushinteger(L, pos.x);
	lua_pushinteger(L, pos.y);
	lua_call(L, 3, 0);
}

bool LuaManager::CallFunctionAvailable(string fn, unitID unit) {
	lua_getglobal(L, fn.c_str());
	lua_pushinteger(L, unit);
	lua_call(L, 1, 0);
	return lua_toboolean(L, 0);
}

LuaManager::~LuaManager() {
	lua_close(L);
}

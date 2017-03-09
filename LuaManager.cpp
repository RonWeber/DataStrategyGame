#include "GlobalIncludes.hpp"
#include "LuaManager.hpp"
#include "GameDynamicData.hpp"

LuaManager lua;

//Functions lua code calls
static int getValue(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -1);
	const char* key = lua_tostring(L, -2);
	lua_pushinteger(L, dynamicData.getValue(unitID, key));
	return 1;
}

static int setValue(lua_State *L) {
	int unitID = (int)lua_tointeger(L, -1);
	const char* key = lua_tostring(L, -2);
	int value = (int)lua_tointeger(L, -3);
	dynamicData.setValue(unitID, key, value);
	return 0;
}


//LuaManager itself
LuaManager::LuaManager() {
	L = luaL_newstate();

	lua_pushcfunction(L, getValue);
	lua_setglobal(L, "getValue");
	lua_pushcfunction(L, setValue);
	lua_setglobal(L, "setValue");
}

void LuaManager::loadFile(string filename) {
	luaL_loadfile(L, filename.c_str());
}

void LuaManager::CallFunction(string fn, int unitID) {
	lua_getglobal(L, fn.c_str());
	lua_pushinteger(L, unitID);
	lua_call(L, 1, 0);
}

bool LuaManager::CallFunctionAvailable(string fn, int unitID) {
	lua_getglobal(L, fn.c_str());
	lua_pushinteger(L, unitID);
	lua_call(L, 1, 0);
	return lua_toboolean(L, 0);
}

LuaManager::~LuaManager() {
	lua_close(L);
}

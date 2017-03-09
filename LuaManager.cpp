#include "GlobalIncludes.hpp"
#include "LuaManager.hpp"
#include "GameDynamicData.hpp"

LuaManager lua;

LuaManager::LuaManager() {
	L = luaL_newstate();

}

void LuaManager::loadFile(string filename) {
	luaL_loadfile(L, filename.c_str());
}

void LuaManager::CallFunction(string fn) {
	lua_getglobal(L, fn.c_str());
	lua_call(L, 0, 0);
}

LuaManager::~LuaManager() {
	lua_close(L);
}

//Functions lua code calls
static int getValue(lua_State *L) {
	int n = lua_gettop(L);    /* number of arguments */
	if (n != 2) {//throw?
		std::cout << "getValue from lua incorrect argument count\n";
	}
	lua_pushinteger(L, dynamicData.getValue(lua_tointeger(L, 0), lua_tostring(L, 1)));
	return 1;
}

static int setValue(lua_State *L) {
	int n = lua_gettop(L);    /* number of arguments */
	if (n != 3) {//throw?
		std::cout << "setValue from lua incorrect argument count\n";
	}
	dynamicData.setValue(lua_tointeger(L, 0), lua_tostring(L, 1), lua_tointeger(L, 2));
	return 0;
}

#include "GlobalIncludes.hpp"
#include "LuaManager.hpp"

LuaManager lua;

LuaManager::LuaManager() {
	L = luaL_newstate();

}

void LuaManager::loadFile(string filename) {
	luaL_loadfile(L, filename.c_str());
}

LuaManager::~LuaManager() {
	lua_close(L);
}


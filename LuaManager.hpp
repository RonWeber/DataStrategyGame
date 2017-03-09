#pragma once
#include "lua.hpp"


class LuaManager {
public:
	LuaManager();
	~LuaManager();
	void loadFile(string filename);
private:
	lua_State* L;

};
extern LuaManager lua; //Defined in Lua.cpp

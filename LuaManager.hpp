#pragma once
#include "lua.hpp"


class LuaManager {
public:
	LuaManager();
	~LuaManager();
	void loadFile(string filename);
	void CallFunction(string fn, int unitID);
	bool CallFunctionAvailable(string fn, int unitID);
private:
	lua_State* L;

};
extern LuaManager lua; //Defined in Lua.cpp

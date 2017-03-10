#pragma once
#include "lua.hpp"
#include "Unit.hpp"


class LuaManager {
public:
	LuaManager();
	~LuaManager();
	void loadFile(string filename);
	void CallFunction(string fn, unitID unit);
	void CallFunction(string fn, unitID unit, coord position);
	bool CallFunctionAvailable(string fn, unitID unit);
private:
	lua_State* L;

};
extern LuaManager lua; //Defined in Lua.cpp

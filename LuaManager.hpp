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
	std::unique_ptr<std::vector<coord>> CallFunctionAllowedLocations(string fn, unitID unit);

#ifndef TWOBLUECUBES_CATCH_HPP_INCLUDED
private:
#endif
	lua_State* L;

};
extern LuaManager lua; //Defined in Lua.cpp

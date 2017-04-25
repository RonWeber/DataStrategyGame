#pragma once
#include "lua.hpp"
#include "Unit.hpp"
#include <unordered_set>


class LuaManager {
public:
	LuaManager();
	~LuaManager();
	void loadFile(string filename);
	void CallFunction(string fn, unitID unit);
	void CallFunction(string fn, unitID unit, coord position);
	bool CallFunctionAvailable(string fn, unitID unit);
	std::unique_ptr<std::unordered_set<coord>> CallFunctionAllowedLocations(string fn, unitID unit);

#ifndef TWOBLUECUBES_CATCH_HPP_INCLUDED
private:
#endif
	lua_State* L;

};

extern std::unique_ptr<LuaManager> lua; //Defined in Lua.cpp, set in main
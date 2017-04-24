#include "catch.hpp"
#include "GlobalIncludes.hpp"
#include "LuaManager.hpp"

//WARNING: several of these tests require DynamicData and StaticData functionality to work correctly.

TEST_CASE("Can lua exist without crashing") {
	std::cout << "lua!" << std::endl;
	lua_pushinteger(lua.L, 17);
	lua_setglobal(lua.L, "value");
	lua_getglobal(lua.L, "value");
	REQUIRE(lua_tointeger(lua.L, -1)==17);
}

TEST_CASE("Can lua load a function from a file, then run it?") {
	lua.loadFile("testData/luaManager.lua");
	lua_pushinteger(lua.L, 17);
	lua_setglobal(lua.L, "value");
	lua.CallFunction("setValue", 5);
	lua_getglobal(lua.L, "value");
	REQUIRE(lua_tointeger(lua.L, -1) == 5);
}


bool success;
static int reportSuccess(lua_State *L) {
	success = true;
	std::cout << "Success!" << std::endl;
	return 0;
}

TEST_CASE("Can lua code run c code?") {
	success = false;

	lua_pushcfunction(lua.L, reportSuccess);
	lua_setglobal(lua.L, "reportSuccess");

	lua.CallFunction("checkReportSuccess", 0);
	REQUIRE(success);
}

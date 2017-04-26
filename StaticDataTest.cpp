#include "catch.hpp"
#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "AbilityType.hpp"
#include "Window.hpp"
#include "LuaManager.hpp"

#ifdef _WIN32
#include <direct.h>
#elif __unix__
#include <unistd.h>
#endif

TEST_CASE("Test constructor of ability.") {
	json test = "{\
      \"id\": \"selfPunch\",\
      \"description\": \"Punches self to make room\",\
      \"Image\": \"games/testgame/ClawPunch.png\",\
      \"selection\": false,\
      \"availableFn\": \"selfPunchAvailable\",\
      \"actionFn\": \"selfPunchAction\",\
      \"helperDataFn\": \"selfPunchHelperData\"\
    }"_json;
	AbilityType type = AbilityType(test);
	CHECK(type.id == "selfPunch");
	CHECK(type.Name == "Punches self to make room");
	CHECK(type.selectionAbility == false);
	REQUIRE(type.functionNames.size() == 3);
	CHECK(type.functionNames.at(Available) == "selfPunchAvailable");
	CHECK(type.functionNames.at(Action) == "selfPunchAction");
	CHECK(type.functionNames.at(HelperData) == "selfPunchHelperData");
}

const json testUnitType = "{\
      \"id\": \"b\",\
      \"side\": 0,\
      \"Image\": \"games/testgame/ClawPunch.png\",\
      \"maxHP\": 10,\
      \"maxMoves\": 2,\
      \"maxAP\": 1,\
      \"extraData\": {\
        \"Bear?\" : 1,\
		\"magicResistance\" : 12\
	   },\
      \"abilities\": [\
        \"selfPunch\"\
      ],\
      \"name\": \"Bear\",\
      \"description\": \"Its a bear.\"\
    }"_json;
TEST_CASE("Test constructor of UnitType") {
	UnitType ut(testUnitType);
	CHECK(ut.id == 'b');
	CHECK(ut.maxHP == 10);
	CHECK(ut.movesPerTurn == 2);
	CHECK(ut.actionsPerTurn == 1);
	REQUIRE(ut.extraData.size() == 2);
	CHECK(ut.extraData["Bear?"] == 1);
	CHECK(ut.extraData["magicResistance"] == 12);	
	REQUIRE(ut.abilities.size() == 1);
	CHECK(ut.abilities[0] == "selfPunch");
	CHECK(ut.name == "Bear");
	CHECK(ut.side == 0);
}

TEST_CASE("Test the ability of UnitType to make a unit") {
	dynamicData = std::unique_ptr<GameDynamicData>(new GameDynamicData(10, 10));
	dynamicData->highestUnitID = 55;
	UnitType ut(testUnitType);
	Unit u = ut.makeUnit({5, 4});
	CHECK(u.id == 56);
	REQUIRE(u.data_keys.size() == 5);
	CHECK(u.data_keys["Bear?"] == 1);
	CHECK(u.data_keys["magicResistance"] == 12);
	CHECK(u.data_keys["hp"] == 10);
	CHECK(u.data_keys["movesRemaining"] == 2);
	CHECK(u.data_keys["actionsRemaining"] == 1);	
	CHECK(u.unitTypeID == ut.id);
	REQUIRE(u.abilities.size() == 1);
	CHECK(u.abilities[0] == "selfPunch");
	CHECK(u.owner == 0);
}

TEST_CASE("A game is loaded from the predetermined file.") {
	gfx = std::unique_ptr<Window>(new Window());
	lua = std::unique_ptr<LuaManager>(new LuaManager());
	(void)chdir("games/testgame/");	
	Game testGame("game.json", 20, 15);
	(void)chdir("../..");		
}

#include "catch.hpp"
#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "AbilityType.hpp"

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

TEST_CASE("Test constructor of UnitType") {
	json test = "{\
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
	UnitType ut(test);
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
	CHECK(ut.description == "Its a bear.");
	CHECK(ut.side == 0);
}

TEST_CASE("A game is loaded from the predetermined file.") {
	(void)chdir("games/testgame/");	
	//Game testGame("game.json");
	(void)chdir("../..");		
}

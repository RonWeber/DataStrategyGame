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
      \"imageFile\": \"games/testgame/ClawPunch.png\",\
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
      \"Image\": \"tmp2.png\",\
      \"maxHP\": 10,\
      \"maxMoves\": 2,\
      \"maxAP\": 1,\
      \"extraData\": [\
        {\
          \"key\": \"Bear?\",\
          \"value\": 1\
        },\
        {\
          \"key\": \"magicResistance\",\
          \"value\": 12\
        }\
      ],\
      \"abilities\": [\
        \"selfPunch\"\
      ],\
      \"name\": \"Bear\",\
      \"description\": \"A very, very scary animal.  If one mauls you, you get an Oscar.\"\
    }"_json;
}

TEST_CASE("A game is loaded from the predetermined file.") {
	(void)chdir("games/testgame/");	
	Game testGame("game.json");
}

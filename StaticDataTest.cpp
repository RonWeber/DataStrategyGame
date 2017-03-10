#include "catch.hpp"
#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "AbilityType.hpp"

#ifdef _WIN32
#include <direct.h>
#elif __unix__
#include <unistd.h>
#endif

TEST_CASE("Test ability.") {
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

TEST_CASE("A game is loaded from the predetermined file.") {
	(void)chdir("games/testgame/");	
	Game testGame("game.json");
}

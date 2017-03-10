#include "catch.hpp"
#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "AbilityType.hpp"

TEST_CASE("Test ability.") {
	json test = "{\
      \"id\": \"selfPunch\",\
      \"description\": \"Punches self to make room\",\
      \"imageFile\": \"selfPunch.png\",\
      \"selection\": false,\
      \"availableFn\": \"selfPunchAvailable\",\
      \"actionFn\": \"selfPunchAction\",\
      \"helperDataFn\": \"selfPunchHelperData\"\
    }"_json;
	AbilityType type = AbilityType(test);
}

TEST_CASE("A game is loaded from the predetermined file.") {
	Game testGame("games/testgame/game.json");
}

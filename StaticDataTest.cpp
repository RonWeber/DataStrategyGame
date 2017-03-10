#include "catch.hpp"
#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "AbilityType.hpp"

TEST_CASE("Test ability.") {
	string test = "{\
      \"id\": \"selfPunch\",
      \"description\": \"Punches self to make room\",
      \"imageFile\": \"selfPunch.png\",
      \"selection\": false,
      \"availableFn\": \"selfPunchAvailable\",
      \"actionFn\": \"selfPunchAction\",
      \"helperDataFn\": \"selfPunchHelperData\"
    }";
	AbilityType 

TEST_CASE("A game is loaded from the predetermined file.") {
	Game testGame("games/testgame/game.json");
}

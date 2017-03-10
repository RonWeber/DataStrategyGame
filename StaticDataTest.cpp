#include "catch.hpp"
#include "Game.hpp"

TEST_CASE("A game is loaded from the predetermined file.") {
	REQUIRE_NOTHROW(Game testGame("games/

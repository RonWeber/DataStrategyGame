#include "catch.hpp"
#include "GameDynamicData.hpp"
#include "GlobalIncludes.hpp"
#include "UnitType.hpp"
#include "Window.hpp"

TEST_CASE("Test the constructor for an empty dynamic data") {
	GameDynamicData emptyData(15, 5);
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 15; y++) {
			bool success = emptyData.terrain[x][y] == '\0';
			CHECK(success);
		}
	}
	bool success = emptyData.highestUnitID == 0;
	CHECK(success);
	success = emptyData.currentPlayer == 0;
	CHECK(success);
}

const json testUnitType = "{\
      \"id\": \"b\",\
      \"side\": 1,\
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
TEST_CASE("Testing the unit methods of dynamic data") {
	gfx = std::unique_ptr<Window>(new Window());
	GameDynamicData data(10, 10);
	UnitType ut(testUnitType);
	coord startingCoord = {5, 4};
	Unit unitToAdd = ut.makeUnit(startingCoord);
	data.addExistingUnit(unitToAdd);
	unitID id = unitToAdd.id;
	Unit &u = data.units.at(id);	
	data.setValue(id, "KEY", 800);
	REQUIRE(data.getValue(id, "KEY") == 800);
	REQUIRE(data.getOwner(id) == 1);
	REQUIRE(data.getPos(id) == startingCoord);
	REQUIRE(data.unitAt(startingCoord) == id);
	coord newCoord = {7, 7};
	data.setPos(id, newCoord);
	REQUIRE(data.unitAt(newCoord) == id);
	REQUIRE(data.unitAt(startingCoord) == NO_UNIT);
	REQUIRE(u.coordinate == newCoord);
	data.addAbility(id, "ABILITY");
	REQUIRE(std::find(u.abilities.begin(), u.abilities.end(), "ABILITY") != u.abilities.end());
	data.removeAbility(id, "ABILITY");
	REQUIRE(std::find(u.abilities.begin(), u.abilities.end(), "ABILITY") == u.abilities.end());
	data.deleteUnit(id);
	REQUIRE(data.units.size() == 0);
	REQUIRE(data.unitAt(newCoord) == NO_UNIT);
}

TEST_CASE("Testing the terrain methods of dynamic data") {
	GameDynamicData data(10, 10);	
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			data.setTerrain(x, y, x+y);
		}
	}
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			CHECK(data.getTerrain(x, y) == x+y);
		}
	}
}

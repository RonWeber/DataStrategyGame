#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include <iostream>

std::unique_ptr<Game> game;

Game::Game(string globalFileName) {
	//initialize data
	std::ifstream file(globalFileName);
    
	json json;


	file >> json;
	displayRNG = json["displayRNG"];
	//TODO: Do something with lua files.
	//TODO: Implement terrain
	for (auto ability : json["abilityData"]) {
		AbilityType newType = AbilityType(ability);
		abilityTypes.insert({ newType.id, newType });
	}
	std::cout << "Abilities loaded.\n";
	for (auto unitType : json["unitData"]) {
		UnitType newType = UnitType(unitType);
		unitTypes.insert({newType.id, newType});
	}


	while (1) {
		gfx.InitFrame();
		if (gfx.quit) break;
		ui.update();
		ui.drawBackground();
		ui.drawUnits();
		ui.drawForeground();

		gfx.EndFrame();
    }
}

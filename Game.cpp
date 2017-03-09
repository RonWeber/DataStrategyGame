#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "UI.hpp"

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
	for (auto unitType : json["unitData"]) {
		UnitType newType = UnitType(unitType);
		unitTypes.insert({newType.id, newType});
	}
	
	//run game
	UI ui = UI();

	Image* i = new Image("games/testgame/tmp2.png");

	while (1) {
		gfx.InitFrame();
		if (gfx.quit) break;
		ui.update();

		ui.draw_grid();

		i->draw_at({ 5, 5 });

	gfx.EndFrame();
    }
    delete i;
}

#include "GlobalIncludes.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "UI.hpp"

Game game;

Game::Game() {
    //You shouldn't be doing this.
}

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
	
	
	//run game
	UI ui = UI();
	while (1) {
		gfx.InitFrame();
		if (gfx.quit) break;
		ui.update();

		ui.draw_grid();

		gfx.EndFrame();
    }
}

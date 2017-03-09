#include <iostream>
#include <fstream>
#include <string>
#include "Game.hpp"
#include "json.hpp"

using string = std::string;
using json = nlohmann::json;

Game game;

Game::Game() {
    //You shouldn't be doing this.
}

Game::Game(string globalFileName) {
    std::ifstream file(globalFileName);
    json json;
    file >> json;
    displayRNG = json["displayRNG"];
    //TODO: Do something with lua files.
    //TODO: Implement terrain
    for (auto ability : json["abilityData"]) {
	AbilityType newType = AbilityType(ability);
	abilityTypes.insert({newType.id, newType});
    }
}

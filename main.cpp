#include "GlobalIncludes.hpp"
#include "Map.hpp"
#include "SaveFile.hpp"
#include "Window.hpp"
#include "UI.hpp"
#include "GameDynamicData.hpp"
#include "LuaManager.hpp"
#include <iostream>

#ifdef _WIN32
#include <direct.h>
#elif __unix__
#include <unistd.h>
#endif

void gameLoop();

int main(int argc, char* argv[]) {
	gfx = std::unique_ptr<Window>(new Window());
	lua = std::unique_ptr<LuaManager>(new LuaManager());

	if (argc < 3) {
		std::cerr << "Command line arguments: the directory of the game, then the save or map file" << std::endl;
		return 1;
	}
	
	if (chdir(argv[1]) != 0) {
		std::cerr << "Could not change directory." << std::endl;
		return 1;
	}

	std::ifstream fileTypeDetection(argv[2]);
	if (isdigit(fileTypeDetection.peek())) {
		//It started with a number.  It can't be json, so it's probably a map.
		LoadMap(argv[2]);
	} else {
		//It didn't start with a number.  It can't be a map, so it's probably JSON
		LoadSave(argv[2]);
	}

	ui = std::unique_ptr<UI>(new UI());
	gameLoop();
	
	return 0;
}


void gameLoop() {
	
	while (1) {
		gfx->InitFrame();
		if (gfx->quit) break;
		ui->update();
		dynamicData->update();
		ui->draw();

		gfx->EndFrame();
	}
}

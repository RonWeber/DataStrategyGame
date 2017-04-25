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
#include <stdlib.h>
#elif __unix__
#include <unistd.h>
#include <libgen.h>
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
	}
	LoadMap(argv[2]);

	//chdir("games/testgame/");
    //LoadMap("testgamebigmap.txt");
	//LoadSave("save.sav");

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

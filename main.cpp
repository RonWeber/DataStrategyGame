#include "GlobalIncludes.hpp"
#include "Map.hpp"
#include "SaveFile.hpp"
#include "Window.hpp"
#include "UI.hpp"
#include "GameDynamicData.hpp"
#include "LuaManager.hpp"

#ifdef _WIN32
#include <direct.h>
#elif __unix__
#include <unistd.h>
#endif

void gameLoop();

int main(int argc, char* argv[]) {
	gfx = std::unique_ptr<Window>(new Window());
	lua = std::unique_ptr<LuaManager>(new LuaManager());

	chdir("games/chessClone/");
	LoadMap("normalChessBoard.txt");

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

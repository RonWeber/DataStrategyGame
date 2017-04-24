#include "GlobalIncludes.hpp"
#include "Map.hpp"
#include "SaveFile.hpp"
#include "Window.hpp"
#include "UI.hpp"

#ifdef _WIN32
#include <direct.h>
#elif __unix__
#include <unistd.h>
#endif

void gameLoop();

int main(int argc, char* argv[]) {
	gfx = std::unique_ptr<Window>(new Window());

	chdir("games/testgame/");
	
    LoadMap("testgamebigmap.txt");
	//LoadSave("save.sav");

	gameLoop();
	
	return 0;
}


void gameLoop() {
	ui = std::unique_ptr<UI>(new UI());
	
	while (1) {
		gfx->InitFrame();
		if (gfx->quit) break;
		ui->update();
		ui->draw();

		gfx->EndFrame();
	}
}

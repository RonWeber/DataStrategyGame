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
	
	chdir("games/testgame/");
    LoadMap("testgamemap.txt");
	//LoadSave("save.sav");
	ui = std::unique_ptr<UI>(new UI());

	gameLoop();
	
	return 0;
}


void gameLoop() {
	while (1) {
		gfx.InitFrame();
		if (gfx.quit) break;
		ui->update();
		ui->drawTerrain();
		ui->drawBackground();
		ui->drawUnits();
		ui->drawForeground();

		gfx.EndFrame();
	}
}

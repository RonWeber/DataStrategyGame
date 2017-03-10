#include "GlobalIncludes.hpp"
#include "Map.hpp"
#include <direct.h>  

int main(int argc, char* argv[]) {
	
	_chdir("games/testgame/");
    LoadMap("testgamemap.txt");

	return 0;
}

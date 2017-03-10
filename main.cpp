#include "GlobalIncludes.hpp"
#include "Map.hpp"

#ifdef _WIN32
#include <direct.h>
#elif __unix__
#include <unistd.h>
#endif

int main(int argc, char* argv[]) {
	
	chdir("games/testgame/");
    LoadMap("testgamemap.txt");

	return 0;
}

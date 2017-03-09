#pragma once

class Graphics {
public:
	Graphics();//should probably add options for resolution and the like
	~Graphics();//close everything in destructor

	void InitFrame();
	void EndFrame();


	Sint32 mouseX, mouseY;
	bool clicked;

	bool quit;
	int screenmode;//0 = windowed (default), 1 = 1.5x screen, 2 = fullscreen, 3 = 1.5x fullscreen mode

	const Uint8 *keyboard;
	unsigned long frame;

	int SCREEN_WIDTH = 1024;
	int SCREEN_HEIGHT = 768;

private:
	//Starts up SDL and creates window
	bool initWindow();
	bool initGL();

	//Loads individual image as texture
	SDL_Texture* loadTexture(std::string path);

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;
	SDL_GLContext gContext;

	unsigned int endTime;
};

extern Graphics gfx; //Defined in Graphics.cpp, opened in Main.cpp
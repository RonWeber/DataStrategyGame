#pragma once

class Window {
public:
	Window();//should probably add options for resolution and the like
	~Window();//close everything in destructor

	void InitFrame();
	void EndFrame();


	Sint32 mouseX, mouseY;
	bool Lclicked, Rclicked;

	bool quit;

	const Uint8 *keyboard;
	unsigned long frame;

	int SCREEN_WIDTH = 1024;
	int SCREEN_HEIGHT = 768;

	//Loads individual image as texture
	GLuint loadTexture(std::string path);

private:
	//Starts up SDL and creates window
	bool initWindow();
	bool initGL();


	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;
	SDL_GLContext gContext;

	unsigned int endTime;
	int screenmode;//0 = windowed (default), 1 = 1.5x screen, 2 = fullscreen, 3 = 1.5x fullscreen mode*
};

extern Window gfx; //Defined in Window.cpp, opened in Main.cpp
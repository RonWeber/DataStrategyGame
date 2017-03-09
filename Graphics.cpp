#include "GlobalIncludes.hpp"
#include "Graphics.hpp"

/*Much of the code in this file was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

Graphics gfx;
bool Graphics::initWindow()//0 = windowed (default), 1 = 1.5x screen, 2 = fullscreen, 3 = 1.5x fullscreen mode
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//Create window
		switch (screenmode) {
		case 1:
			gWindow = SDL_CreateWindow("Frictionless", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*1.5, SCREEN_HEIGHT*1.5, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			break;
		case 2:
			gWindow = SDL_CreateWindow("Frictionless", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
			break;
		case 3:
			gWindow = SDL_CreateWindow("Frictionless", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*1.5, SCREEN_HEIGHT*1.5, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
			break;
		default:
			gWindow = SDL_CreateWindow("Frictionless", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		}
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Use Vsync
				if (SDL_GL_SetSwapInterval(0) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				//Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
}


bool Graphics::initGL()
{
	GLenum error = GL_NO_ERROR;

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! %s\n" << error;
		return false;
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! %s\n" << error;
		return false;
	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! %s\n" << error;
		return false;
	}

	glEnable(GL_MULTISAMPLE);

	return true;
}

SDL_Texture* Graphics::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}


Graphics::Graphics() {
	screenmode = 0;
	initWindow();

	glLoadIdentity();
	glTranslated(-1, 1, 0);
	glScaled(2.0 / SCREEN_WIDTH, -2.0 / SCREEN_HEIGHT, 1.0);

	quit = false;
	keyboard = SDL_GetKeyboardState(NULL);

	frame = 0;
	endTime = SDL_GetTicks();

}

Graphics::~Graphics() {
	//Destroy window    
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Graphics::InitFrame() {
	SDL_Event e;
	endTime = endTime + 17;
	frame++;
	if (frame % 3 == 0) endTime--;
	//Handle events on queue
	SDL_Scancode keydown = SDL_SCANCODE_UNKNOWN;
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		if (e.type == SDL_MOUSEMOTION) {
			//Get the mouse offsets 
			mouseX = e.motion.x;
			mouseY = e.motion.y;
			if (screenmode == 1 || screenmode == 3) {
				mouseX /= 1.5;
				mouseY /= 1.5;
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			mouseX = e.button.x;
			mouseY = e.button.y;
			if (e.button.button == SDL_BUTTON_LEFT)
				clicked = (e.button.state == SDL_PRESSED);
			if (screenmode == 1 || screenmode == 3) {
				mouseX /= 1.5;
				mouseY /= 1.5;
			}
		}
		if (e.type == SDL_KEYDOWN) {
			keydown = e.key.keysym.scancode;
		}
	}
	if (keyboard[SDL_SCANCODE_ESCAPE]) {
		quit = true;
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::EndFrame() {
	//Update screen
	SDL_GL_SwapWindow(gWindow);
	if (SDL_GetTicks() < endTime) {
		//Sleep the remaining frame time
		SDL_Delay(endTime - SDL_GetTicks());
	}
	else {
		//std::cout << SDL_GetTicks()-endTime << "\n";
	}

}
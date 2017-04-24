#include "GlobalIncludes.hpp"
#include "Window.hpp"
#include "SaveFile.hpp"

/*Much of the code in this file was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

std::unique_ptr<Window> gfx;
bool Window::initWindow()//0 = windowed (default), 1 = 1.5x screen, 2 = fullscreen, 3 = 1.5x fullscreen mode
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

		gWindow = SDL_CreateWindow("Data Strategy Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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


bool Window::initGL()
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

GLuint Window::loadTexture(std::string path)
{
	GLuint TextureID;
	SDL_Surface* Surface = IMG_Load(path.c_str());
	if (Surface == NULL)
	{
		std::cerr << "Unable to load image! SDL_image Error: " << IMG_GetError() << "\n";
		//throw?
	}
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	int Mode = GL_RGB;

	if (Surface->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "openGL error" << err << "\n";
		//throw?
	}

	glDisable(GL_TEXTURE_2D);
	SDL_FreeSurface(Surface);

	return TextureID;//increment for next texture
}


Window::Window() {
	initWindow();

	glLoadIdentity();
	glTranslated(-1, 1, 0);
	glScaled(2.0 / SCREEN_WIDTH, -2.0 / SCREEN_HEIGHT, 1.0);

	quit = false;
	keyboard = SDL_GetKeyboardState(NULL);

	frame = 0;
	endTime = SDL_GetTicks();

	Lclicked = Rclicked = false;

}

Window::~Window() {
	//Destroy window    
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Window::InitFrame() {
	SDL_Event e;
	endTime = endTime + 17;
	frame++;
	if (frame % 3 == 0) endTime--;
	//Handle events on queue
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
		}
		if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			mouseX = e.button.x;
			mouseY = e.button.y;
			if (e.button.button == SDL_BUTTON_LEFT)
				Lclicked = (e.button.state == SDL_PRESSED);
			if (e.button.button == SDL_BUTTON_RIGHT)
				Rclicked = (e.button.state == SDL_PRESSED);
		}
		if (e.type == SDL_KEYDOWN) {
			SDL_Keycode keydown = e.key.keysym.sym;
			if (keydown == SDLK_UP)
				scrollU = true;
			if (keydown == SDLK_DOWN)
				scrollD = true;
			if (keydown == SDLK_LEFT)
				scrollL = true;
			if (keydown == SDLK_RIGHT)
				scrollR = true;
			//TODO: This is a temporary hack to test saving.  Add a real save UI.
			//Note: Nothing is more permanent than a temporary hack.
			if (keydown == SDLK_s)
				Save("save.sav");
		}
		if (e.type == SDL_KEYUP) {
			SDL_Keycode keydown = e.key.keysym.sym;
			if (keydown == SDLK_UP)
				scrollU = false;
			if (keydown == SDLK_DOWN)
				scrollD = false;
			if (keydown == SDLK_LEFT)
				scrollL = false;
			if (keydown == SDLK_RIGHT)
				scrollR = false;
		}
	}
	if (keyboard[SDL_SCANCODE_ESCAPE]) {
		quit = true;
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::EndFrame() {
	//Update screen
	SDL_GL_SwapWindow(gWindow);
	if (SDL_GetTicks() < endTime) {
		//Sleep the remaining frame time
		SDL_Delay(endTime - SDL_GetTicks());
	}
	else {
		//std::cout << SDL_GetTicks()-endTime << "\n";
	}

	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR)
		std::cout << "GL error!" << err << "\n";

}

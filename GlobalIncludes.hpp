#pragma once
//This is a precompiled header
#include <iostream>
#include <fstream>
#include <string>
#include "include/json.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define GLEW_STATIC
#include <glew.h>
#define NO_SDL_GLEXT
#include <SDL2/SDL_opengl.h>


using json = nlohmann::json;
using string = std::string;
using ifstream = std::ifstream;

typedef struct {
	int x, y;
} coord;

typedef char TerrainID;

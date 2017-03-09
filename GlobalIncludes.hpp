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


static double xdir(double angle, double distance) {
	return -sin((angle * M_PI) / 180)*distance;
}
static double ydir(double angle, double distance) {
	return cos((angle * M_PI) / 180)*distance;
}
static bool bbox(double x, double y, double x1, double y1, double w, double h) {
	return ((x >= x1 && x <= x1 + w) && (y >= y1 && y <= y1 + h));
}

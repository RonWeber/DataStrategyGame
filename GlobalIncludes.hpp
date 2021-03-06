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

struct coord {
	int x, y;
} ;
inline bool operator==(const coord& lhs, const coord& rhs) {
	return lhs.x == rhs.x &&
		lhs.y == rhs.y;
}
namespace std {
	template <>
	struct hash<coord> {
		size_t operator()(const coord& k) const {
			return ((hash<int>()(k.x))^(hash<int>()(-k.y)));
		}
	};
}

typedef char TerrainID;
typedef int sideID;

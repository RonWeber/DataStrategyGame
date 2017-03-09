#pragma once
#include "Window.hpp"

class Image {
public:
	Image(string filename);
	void draw_at(int x, int y);
private:
	GLuint img;
};

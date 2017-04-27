#pragma once

class Image {
public:
	Image(string filename, bool forceGrid);
	void draw_at(coord pos);
	void draw_at(coord pos, float offsetX, float offsetY);
	void draw_absolute(coord pos);
	int width, height;
private:
	GLuint img;
};

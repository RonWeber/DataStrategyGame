#pragma once

class Image {
public:
	Image(string filename);
	void draw_at(coord pos);
	void draw_absolute(coord pos);
private:
	GLuint img;
};

#pragma once

class Image {
public:
	Image(string filename);
	void draw_at(coord pos);
private:
	GLuint img;
};

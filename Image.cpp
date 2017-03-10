#include "GlobalIncludes.hpp"
#include "Image.hpp"
#include "Window.hpp"
#include "UI.hpp"

Image::Image(string filename) {
	img = gfx.loadTexture(filename);
}


#pragma warning( push )
#pragma warning( disable : 4244)
void Image::draw_at(coord pos) {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, img);

	glColor3f(1.0f, 1.0f, 1.0f);
	int x = pos.x;
	int y = pos.y;
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(32*x, 32 * y + 32);
	glTexCoord2f(1, 1);
	glVertex2f(32 * x + 32, 32 * y + 32);
	glTexCoord2f(1, 0);
	glVertex2f(32 * x + 32, 32 * y);
	glTexCoord2f(0, 0);
	glVertex2f(32 * x, 32 * y);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
#pragma warning( pop )
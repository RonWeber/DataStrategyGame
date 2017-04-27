#include "GlobalIncludes.hpp"
#include "Image.hpp"
#include "Window.hpp"
#include "UI.hpp"
#include "Game.hpp"

Image::Image(string filename, bool forceResize) {
	auto data = gfx->loadTexture(filename);
	img = data.tex;
	if (forceResize) {
		width = gridSize;
		height = gridSize;
	}
	else {
		width = data.width;
		height = data.height;
	}
}


#pragma warning( push )
#pragma warning( disable : 4244)
void Image::draw_at(coord pos) {
	draw_at(pos, 0.f, 0.f);
}
void Image::draw_at(coord pos, float offsetX, float offsetY) {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, img);

	glColor3f(1.0f, 1.0f, 1.0f);
	int x = pos.x;
	int y = pos.y;
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(gridSize * x - ui->scrollOffsetX + offsetX, gridSize * y + height - ui->scrollOffsetY + offsetY);
	glTexCoord2f(1, 1);
	glVertex2f(gridSize * x + width - ui->scrollOffsetX + offsetX, gridSize * y + height - ui->scrollOffsetY + offsetY);
	glTexCoord2f(1, 0);
	glVertex2f(gridSize * x + width - ui->scrollOffsetX + offsetX, gridSize * y - ui->scrollOffsetY + offsetY);
	glTexCoord2f(0, 0);
	glVertex2f(gridSize * x - ui->scrollOffsetX + offsetX, gridSize * y - ui->scrollOffsetY + offsetY);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
void Image::draw_absolute(coord pos) {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, img);

	glColor3f(1.0f, 1.0f, 1.0f);
	int x = pos.x;
	int y = pos.y;
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(gridSize * x, gridSize * y + height);
	glTexCoord2f(1, 1);
	glVertex2f(gridSize * x + width, gridSize * y + height);
	glTexCoord2f(1, 0);
	glVertex2f(gridSize * x + width, gridSize * y );
	glTexCoord2f(0, 0);
	glVertex2f(gridSize * x , gridSize * y );
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
#pragma warning( pop )

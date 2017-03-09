#include "GlobalIncludes.hpp"
#include "UI.hpp"
#include "Window.hpp"

void UI::update() {
	gridX = gfx.mouseX / 32;
	gridY = gfx.mouseY / 32;

	if (gfx.Lclicked) {
		switch (selectionLevel) {
		case none:
			selectionLevel = unit;
			//unitSelected = getUnitAt(gridX,gridY)
			break;
		case unit:
			selectionLevel = ability;
			break;
		case ability:
			//do ability
			break;
		}
	}

	if (gfx.Rclicked) {
		switch (selectionLevel) {
		case none:
			break;
		case unit:
			selectionLevel = none;
			break;
		case ability:
			selectionLevel = unit;
			break;
		}
	}
}

#pragma warning( push )
#pragma warning( disable : 4244)

void UI::draw_grid() {
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex2f(gridX * 32, gridY * 32);
	glVertex2f(gridX * 32 + 32, gridY * 32);
	glVertex2f(gridX * 32, gridY * 32 + 32);
	glVertex2f(gridX * 32 + 32, gridY * 32 + 32);
	glEnd();



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (double x = 0; x < gfx.SCREEN_WIDTH + 20; x += 32) {
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x - 5, 0);
		glVertex2f(x - 5, gfx.SCREEN_HEIGHT);
		glColor3f(0.05f, 0.05f, .4f);
		glVertex2f(x, 0);
		glVertex2f(x, gfx.SCREEN_HEIGHT);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x + 5, 0);
		glVertex2f(x + 5, gfx.SCREEN_HEIGHT);
		glEnd();
	}
	for (double y = 0; y < gfx.SCREEN_HEIGHT + 20; y += 32) {
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(0, y - 5);
		glVertex2f(gfx.SCREEN_WIDTH, y - 5);
		glColor3f(0.05f, 0.05f, .4f);
		glVertex2f(0, y);
		glVertex2f(gfx.SCREEN_WIDTH, y);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(0, y + 5);
		glVertex2f(gfx.SCREEN_WIDTH, y + 5);
		glEnd();
	}


	glDisable(GL_BLEND);
}

#pragma warning( pop ) 
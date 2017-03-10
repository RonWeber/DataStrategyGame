#include "GlobalIncludes.hpp"
#include "UI.hpp"
#include "Window.hpp"
#include "LuaManager.hpp"
UI::UI() {
	scrollOffsetX = scrollOffsetY = 0;
}
void UI::update() {
	gridX = (gfx.mouseX - scrollOffsetX) / 32;
	gridY = (gfx.mouseY - scrollOffsetY) / 32;

	if (gfx.Lclicked) {
		switch (selectionLevel) {
		case none:
			selectionLevel = unit;
			//unitSelected = getUnitAt(gridX,gridY)
			break;
		case unit:
			/*abilitySelected = 
			if (ability is available){
				if (ability is instant)
					lua.callFunction(unitSlected, AbilitySelected)
				else
					selectionLevel = ability;
			}*/
			break;
		case ability:
			//coord c = coord(gridX, gridY)
			//if c is valid{
			//lua.callFunction(unitSelected, AbilitySelected, c)
			//selectionLevel = unit
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

void UI::drawBackground() {
	//draw square selection
	int chosenX, chosenY;
	switch (selectionLevel) {
		//draw current selection
	case none: chosenX = gridX; chosenY = gridY;
	case ability:
		//highlight currently selected ability
	case unit:
		//draw all abilities of unit
		break;
	}
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


void UI::drawForeground() {
	switch (selectionLevel) {
	case none: break;
	case ability:
		//highlight currently selected ability
	case unit:
		//draw all abilities of unit
		break;
	}
	//draw tooltips
}

#pragma warning( pop ) 
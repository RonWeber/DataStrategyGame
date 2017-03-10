#include "GlobalIncludes.hpp"
#include "UI.hpp"
#include "Window.hpp"
#include "LuaManager.hpp"
#include "GamedynamicData.hpp"
#include "Unit.hpp"
#include "Game.hpp"
std::unique_ptr<UI> ui;
UI::UI() {
	scrollOffsetX = scrollOffsetY = 0;
}
void UI::update() {
	gridX = (gfx.mouseX - scrollOffsetX) / 32;
	gridY = (gfx.mouseY - scrollOffsetY) / 32;

	if (gfx.Lclicked) {
		switch (selectionLevel) {
		case none:
			unitSelected = dynamicData->unitAt({ gridX,gridY });
			if (unitSelected != -1) {
				selectionLevel = unit;
			}
			break;
		case unit:
			if (gridY == 600 / 32 && gridX < dynamicData->units[unitSelected].abilities.size()) {
				abilitySelected = dynamicData->units[unitSelected].abilities[gridX];
				if (lua.CallFunctionAvailable(abilitySelected, unitSelected)) {
					if (game->abilityTypes.at(abilitySelected).selectionAbility)
						selectionLevel = ability;
					else
						lua.CallFunction(abilitySelected, unitSelected);
				}
			}
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
void drawSquare(coord pos, float r, float g, float b) {
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex2f(pos.x * 32, pos.y * 32);
	glVertex2f(pos.x * 32 + 32, pos.y * 32);
	glVertex2f(pos.x * 32, pos.y * 32 + 32);
	glVertex2f(pos.x * 32 + 32, pos.y * 32 + 32);
	glEnd();

}

void UI::drawBackground() {
	//draw square selection
	switch (selectionLevel) {
	case none:
		drawSquare({ gridX, gridY }, .6f, .6f, .6f);
		break;
	case unit:
		drawSquare(dynamicData->getPos(unitSelected), .6f, .6f, .6f);
		break;
	case ability:
		drawSquare({ gridX, gridY }, .4f, .4f, .4f);
		drawSquare(dynamicData->getPos(unitSelected), .6f, .6f, .6f);
		break;
	}



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


void UI::drawUnits() {
	for(unitID uID: dynamicData->getAllUnits()) {
		Unit u = dynamicData->units.at(uID);
		game->unitTypes.at(u.unitTypeID).image->draw_at(u.coordinate);
	}
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
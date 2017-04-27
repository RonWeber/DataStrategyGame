#include <iostream>
#include "GlobalIncludes.hpp"
#include "UI.hpp"
#include "Window.hpp"
#include "LuaManager.hpp"
#include "GameDynamicData.hpp"
#include "Unit.hpp"
#include "Game.hpp"
#include "SaveFile.hpp"
std::unique_ptr<UI> ui;

UI::UI() {
	scrollOffsetX = -(gfx->SCREEN_WIDTH - (game->mapWidth * gridSize)) / 2;
	scrollOffsetY = -(gfx->SCREEN_HEIGHT - (game->mapHeight * gridSize)) / 2;
}
void UI::draw() {
	drawTerrain();
	drawBackground();
	drawUnits();
	drawUnitsHUD();
	drawForeground();
}
#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4244)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif
void UI::clearSelection() {
	selectionLevel = none;
}
void UI::update() {
	scroll();
	gridX = (gfx->mouseX + scrollOffsetX) / gridSize;
	gridY = (gfx->mouseY + scrollOffsetY) / gridSize;

	if (gfx->Lclicked) {
		switch (selectionLevel) {
		case none:
			if (game->withinBounds({ gridX, gridY })){
				unitSelected = dynamicData->unitAt({ gridX,gridY });
				if (unitSelected != NO_UNIT) {
					selectionLevel = unit;
				}
			}
			break;
		case unit:
			if (selectedUnitIsOurs() && (gfx->mouseY / gridSize) == (gfx->SCREEN_HEIGHT / gridSize - 1) && (gfx->mouseX / gridSize) < dynamicData->units.at(unitSelected).abilities.size()) {
				abilitySelected = dynamicData->units.at(unitSelected).abilities[(gfx->mouseX / gridSize)];
				auto thisAbility = game->abilityTypes.at(abilitySelected);
				auto fnNames = thisAbility.functionNames;
				if (lua->CallFunctionAvailable(fnNames[LuaFunction::Available], unitSelected)) {
					if (thisAbility.selectionAbility) {
						abilitySelectionPosition = (gfx->mouseX / gridSize);
						selectionLevel = ability;
						allowedLocations = lua->CallFunctionAllowedLocations(fnNames[LuaFunction::AllowedLocations], unitSelected);
					}
					else {
						lua->CallFunction(fnNames[LuaFunction::Action], unitSelected);
					}
				}
			}
			break;
		case ability:
			coord c = { gridX, gridY };
			auto allLocs = allowedLocations.get();
			for (coord locs : *allLocs) {
				if (locs == c) {
					auto thisAbility = game->abilityTypes.at(abilitySelected);
					auto fnNames = thisAbility.functionNames;
					lua->CallFunction(fnNames[LuaFunction::Action], unitSelected, c);
					selectionLevel = unit;
				}
			}
			break;
		}
	}

	if (gfx->Rclicked) {
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
void UI::scroll() {
	const int spd = 8;
	const int maxOffset = 128;
	if (game->mapWidth * gridSize > gfx->SCREEN_WIDTH - maxOffset * 2) {
		if (gfx->scrollL)
			scrollOffsetX -= spd;
		if (gfx->scrollR)
			scrollOffsetX += spd;

		if (scrollOffsetX < -maxOffset)
			scrollOffsetX = -maxOffset;
		if (scrollOffsetX + gfx->SCREEN_WIDTH > (game->mapWidth * gridSize) + maxOffset)
			scrollOffsetX = -gfx->SCREEN_WIDTH + (game->mapWidth * gridSize) + maxOffset;
	}
	if (game->mapHeight * gridSize > gfx->SCREEN_HEIGHT - maxOffset * 2) {
		if (gfx->scrollU)
			scrollOffsetY -= spd;
		if (gfx->scrollD)
			scrollOffsetY += spd;

		if (scrollOffsetY < -maxOffset)
			scrollOffsetY = -maxOffset;
		if (scrollOffsetY + gfx->SCREEN_HEIGHT >(game->mapHeight * gridSize) + maxOffset)
			scrollOffsetY = -gfx->SCREEN_HEIGHT + (game->mapHeight * gridSize) + maxOffset;
	}
}

void UI::drawSquare(coord pos, float r, float g, float b) {
	if (game->withinBounds(pos)) {
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(r, g, b);
		glVertex2f(pos.x * gridSize - scrollOffsetX, pos.y * gridSize - scrollOffsetY);
		glVertex2f(pos.x * gridSize + gridSize - scrollOffsetX, pos.y * gridSize - scrollOffsetY);
glVertex2f(pos.x * gridSize - scrollOffsetX, pos.y * gridSize + gridSize - scrollOffsetY);
glVertex2f(pos.x * gridSize + gridSize - scrollOffsetX, pos.y * gridSize + gridSize - scrollOffsetY);
glEnd();
	}
}
void UI::drawSquare(coord pos, float r, float g, float b, float a) {
	if (game->withinBounds(pos)) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_TRIANGLE_STRIP);
		glColor4f(r, g, b, a);
		glVertex2f(pos.x * gridSize - scrollOffsetX, pos.y * gridSize - scrollOffsetY);
		glVertex2f(pos.x * gridSize + gridSize - scrollOffsetX, pos.y * gridSize - scrollOffsetY);
		glVertex2f(pos.x * gridSize - scrollOffsetX, pos.y * gridSize + gridSize - scrollOffsetY);
		glVertex2f(pos.x * gridSize + gridSize - scrollOffsetX, pos.y * gridSize + gridSize - scrollOffsetY);
		glEnd();
		glDisable(GL_BLEND);
	}
}

void UI::drawBackground() {
	drawGrid(-scrollOffsetX, -scrollOffsetY, game->mapWidth * gridSize, game->mapHeight * gridSize);

	//draw square selection
	switch (selectionLevel) {
	case none:
		drawSquare({ gridX, gridY }, .6f, .6f, .6f);
		break;
	case unit:
		drawSquare(dynamicData->getPos(unitSelected), .6f, .6f, .6f);
		break;
	case ability:
		auto allLocs = allowedLocations.get();
		for (coord locs : *allLocs) {
			drawSquare(locs, .5f, .5f, 1.f, .7);
		}
		drawSquare({ gridX, gridY }, .4f, .4f, .4f);
		drawSquare(dynamicData->getPos(unitSelected), .6f, .6f, .6f);
		break;
	}

}

void UI::drawGrid(double xStart, double yStart, double width, double height) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	const double lineSize = 4;
	for (double x = xStart; x < xStart + width; x += gridSize) {
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x - lineSize, yStart);
		glVertex2f(x - lineSize, yStart + height);
		glColor3f(0.05f, 0.05f, .4f);
		glVertex2f(x, yStart);
		glVertex2f(x, yStart + height);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x + lineSize, yStart);
		glVertex2f(x + lineSize, yStart + height);
		glEnd();
	}
	for (double y = yStart; y < yStart + height; y += gridSize) {
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(xStart, y - lineSize);
		glVertex2f(xStart + width, y - lineSize);
		glColor3f(0.05f, 0.05f, .4f);
		glVertex2f(xStart, y);
		glVertex2f(xStart + width, y);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(xStart, y + lineSize);
		glVertex2f(xStart + width, y + lineSize);
		glEnd();
	}

	glDisable(GL_BLEND);
}

void UI::drawTerrain() {
	for (int x = 0; x < dynamicData->terrain.size(); x++) {
		for (int y = 0; y < dynamicData->terrain[x].size(); y++) {
			TerrainID id = dynamicData->terrain[x][y];
			if (game->terrainTypes.count(id) > 0)
				game->terrainTypes.at(id).image->draw_at({ x,y });
		}
	}
}


void UI::drawUnits() {
	for (unitID uID : dynamicData->getAllUnits()) {
		Unit &u = dynamicData->units.at(uID);
		game->unitTypes.at(u.unitTypeID).image->draw_at(u.coordinate);
	}
}
void UI::drawUnitsHUD() {
	for (unitID uID : dynamicData->getAllUnits()) {
		Unit &u = dynamicData->units.at(uID);
		if (u.owner == dynamicData->currentPlayer) {
			int xx = 0;
			if (game->movementIcon) {
				for (int i = 0; i < u.data_keys["movesRemaining"]; i++) {
					game->movementIcon->draw_at(u.coordinate, xx, gridSize - game->movementIcon->height + game->iconOffset);
					xx += game->movementIconSeperation;
				}
			}
			if (game->actionIcon) {
				for (int i = 0; i < u.data_keys["actionsRemaining"]; i++) {
					game->actionIcon->draw_at(u.coordinate, xx, gridSize - game->actionIcon->height + game->iconOffset);
					xx += (float)game->actionIconSeperation;
				}
			}
		}
	}

	unitID uID = dynamicData->unitAt({ gridX,gridY });
	if (uID != NO_UNIT) {
		int i, xx = 0;
		Unit &u = dynamicData->units.at(uID);
		UnitType &type = game->unitTypes.at(u.unitTypeID);
		if (game->hpIcon) {
			for (i = 0; i < u.data_keys["hp"]; i++) {
				game->hpIcon->draw_at(u.coordinate, xx, gridSize - game->actionIcon->height + game->iconOffset);
				xx += (float)game->actionIconSeperation;
			}
			if (game->hpEmptyIcon) {
				for (; i < type.maxHP; i++) {
					game->hpEmptyIcon->draw_at(u.coordinate, xx, gridSize - game->actionIcon->height + game->iconOffset);
					xx += (float)game->actionIconSeperation;
				}
			}
		}
		
	}
}

void UI::drawForeground() {
	switch (selectionLevel) {
	case none: break;
	case ability:
		drawSquare({ abilitySelectionPosition , gfx->SCREEN_HEIGHT / gridSize - 1 }, .2, .2, .2);
	case unit:
		drawSquare(dynamicData->getPos(unitSelected), 1.f, 1.f, 1.f, 0.2f);//draw second highlighter square
		if (selectedUnitIsOurs()) {
			auto abilities = dynamicData->units.at(unitSelected).abilities;
			for (int i = 0; i < abilities.size(); i++) {
				game->abilityTypes.at(abilities[i]).image->draw_absolute({ i, gfx->SCREEN_HEIGHT / gridSize - 1 });
			}
		}
		break;
	}
	//draw tooltips
}

bool UI::selectedUnitIsOurs() {
	Unit &u = dynamicData->units.at(unitSelected);
	return u.owner == dynamicData->currentPlayer;
}
#ifdef WINgridSize
#pragma warning( pop ) 
#else
#pragma GCC diagnostic pop
#endif

void UI::playerWins(sideID player) {
	std::cout << "BTW player " << player << " won." << std::endl;
}

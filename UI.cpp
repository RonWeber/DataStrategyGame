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
	scrollOffsetX = -(gfx->SCREEN_WIDTH - (game->mapWidth * 32)) / 2;
	scrollOffsetY = -(gfx->SCREEN_HEIGHT - (game->mapHeight * 32)) / 2;
}

void UI::draw() {
	ui->drawTerrain();
	ui->drawBackground();
	ui->drawUnits();
	ui->drawForeground();
}
#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4244)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif
void UI::update() {
	scroll();
	gridX = (gfx->mouseX + scrollOffsetX) / 32;
	gridY = (gfx->mouseY + scrollOffsetY) / 32;

	if (gfx->Lclicked) {
		switch (selectionLevel) {
		case none:
			if (game->withinBounds({ gridX, gridY })){
				unitSelected = dynamicData->unitAt({ gridX,gridY });
				if (unitSelected != -1) {
					selectionLevel = unit;
				}
			}
			break;
		case unit:
			if (selectedUnitIsOurs() && (gfx->mouseY / 32) == (gfx->SCREEN_HEIGHT / 32 - 1) && (gfx->mouseX / 32) < dynamicData->units.at(unitSelected).abilities.size()) {
				abilitySelected = dynamicData->units.at(unitSelected).abilities[(gfx->mouseX / 32)];
				auto thisAbility = game->abilityTypes.at(abilitySelected);
				auto fnNames = thisAbility.functionNames;
				if (lua->CallFunctionAvailable(fnNames[LuaFunction::Available], unitSelected)) {
					if (thisAbility.selectionAbility) {
						abilitySelectionPosition = (gfx->mouseX / 32);
						selectionLevel = ability;
						allowedLocations = lua->CallFunctionAllowedLocations(fnNames[LuaFunction::AllowedLocations], unitSelected);
					}
					else {
						lua->CallFunction(fnNames[LuaFunction::Action], unitSelected);
						selectionLevel = none;
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
					selectionLevel = none;
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
	if (game->mapWidth * 32 > gfx->SCREEN_WIDTH - maxOffset * 2) {
		if (gfx->scrollL)
			scrollOffsetX -= spd;
		if (gfx->scrollR)
			scrollOffsetX += spd;

		if (scrollOffsetX < -maxOffset)
			scrollOffsetX = -maxOffset;
		if (scrollOffsetX + gfx->SCREEN_WIDTH > (game->mapWidth * 32) + maxOffset)
			scrollOffsetX = -gfx->SCREEN_WIDTH + (game->mapWidth * 32) + maxOffset;
	}
	if (game->mapHeight * 32 > gfx->SCREEN_HEIGHT - maxOffset * 2) {
		if (gfx->scrollU)
			scrollOffsetY -= spd;
		if (gfx->scrollD)
			scrollOffsetY += spd;

		if (scrollOffsetY < -maxOffset)
			scrollOffsetY = -maxOffset;
		if (scrollOffsetY + gfx->SCREEN_HEIGHT >(game->mapHeight * 32) + maxOffset)
			scrollOffsetY = -gfx->SCREEN_HEIGHT + (game->mapHeight * 32) + maxOffset;
	}
}

void UI::drawSquare(coord pos, float r, float g, float b) {
	if (game->withinBounds(pos)) {
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(r, g, b);
		glVertex2f(pos.x * 32 - scrollOffsetX, pos.y * 32 - scrollOffsetY);
		glVertex2f(pos.x * 32 + 32 - scrollOffsetX, pos.y * 32 - scrollOffsetY);
		glVertex2f(pos.x * 32 - scrollOffsetX, pos.y * 32 + 32 - scrollOffsetY);
		glVertex2f(pos.x * 32 + 32 - scrollOffsetX, pos.y * 32 + 32 - scrollOffsetY);
		glEnd();
	}
}
void UI::drawSquare(coord pos, float r, float g, float b, float a) {
	if (game->withinBounds(pos)) {
		glEnable(GL_BLEND);
		glBegin(GL_TRIANGLE_STRIP);
		glColor4f(r, g, b, a);
		glVertex2f(pos.x * 32 - scrollOffsetX, pos.y * 32 - scrollOffsetY);
		glVertex2f(pos.x * 32 + 32 - scrollOffsetX, pos.y * 32 - scrollOffsetY);
		glVertex2f(pos.x * 32 - scrollOffsetX, pos.y * 32 + 32 - scrollOffsetY);
		glVertex2f(pos.x * 32 + 32 - scrollOffsetX, pos.y * 32 + 32 - scrollOffsetY);
		glEnd();
		glDisable(GL_BLEND);
	}
}

void UI::drawBackground() {
	drawGrid(-scrollOffsetX, -scrollOffsetY, game->mapWidth*32, game->mapHeight * 32);

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
		for(coord locs: *allLocs) {
			drawSquare(locs, 1, 1, 1, .5);
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
	for (double x = xStart; x < xStart+width; x += 32) {
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x - lineSize, yStart);
		glVertex2f(x - lineSize, yStart+height);
		glColor3f(0.05f, 0.05f, .4f);
		glVertex2f(x, yStart);
		glVertex2f(x, yStart + height);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x + lineSize, yStart);
		glVertex2f(x + lineSize, yStart + height);
		glEnd();
	}
	for (double y = yStart; y < yStart + height; y += 32) {
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(xStart, y - lineSize);
		glVertex2f(xStart+width, y - lineSize);
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
				game->terrainTypes.at(id).image->draw_at({x,y});
		}
	}
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
		drawSquare({ abilitySelectionPosition , gfx->SCREEN_HEIGHT / 32 - 1 }, .2, .2, .2);
	case unit:
		drawSquare(dynamicData->getPos(unitSelected), 1.f, 1.f, 1.f, 0.2f);//draw second highlighter square
		if (selectedUnitIsOurs()) {
			auto abilities = dynamicData->units.at(unitSelected).abilities;
			for (int i = 0; i < abilities.size(); i++) {
				game->abilityTypes.at(abilities[i]).image->draw_absolute({ i, gfx->SCREEN_HEIGHT / 32 - 1 });
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
#ifdef WIN32
#pragma warning( pop ) 
#else
#pragma GCC diagnostic pop
#endif

void UI::playerWins(sideID player) {
	std::cout << "BTW player " << player << " won." << std::endl;
}

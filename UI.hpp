#pragma once
#include "Unit.hpp"
#include <unordered_set>

class UI {
public:
	UI();
	void draw();
	void update();
	int scrollOffsetX = 0;
	int scrollOffsetY = 0;
	void clearSelection();
	void playerWins(sideID player);
private:
	void scroll();
	void drawBackground();
	void drawUnits();
	void drawUnitsHUD();
	void drawTerrain();
	void drawForeground();
	void checkIllegalSelection();
	void drawGrid(double x, double y, double width, double height);
	void drawSquare(coord pos, float r, float g, float b);
	void drawSquare(coord pos, float r, float g, float b, float a);
	void drawSquareAbsolute(coord pos, float r, float g, float b);
	bool selectedUnitIsOurs();
	int gridX, gridY;
	enum selectionType { none = 0, unit, ability };
	selectionType selectionLevel = none;
	unitID unitSelected;
	string abilitySelected;
	int abilitySelectionPosition;
	std::unique_ptr<std::unordered_set<coord>> allowedLocations;
};

extern std::unique_ptr<UI> ui;

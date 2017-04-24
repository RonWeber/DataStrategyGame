#pragma once
#include "Unit.hpp"

class UI {
public:
	UI();
	void draw();
	void update();
	int scrollOffsetX = 0;
	int scrollOffsetY = 0;
private:
	void scroll();
	void drawBackground();
	void drawUnits();
	void drawTerrain();
	void drawForeground();
	void drawGrid(double x, double y, double width, double height);
	void drawSquare(coord pos, float r, float g, float b);
	void drawSquare(coord pos, float r, float g, float b, float a);
	int gridX, gridY;
	enum selectionType { none = 0, unit, ability };
	selectionType selectionLevel = none;
	unitID unitSelected;
	string abilitySelected;
	int abilitySelectionPosition;
	std::unique_ptr<std::vector<coord>> allowedLocations;
};

extern std::unique_ptr<UI> ui;

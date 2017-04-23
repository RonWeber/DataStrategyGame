#pragma once
#include "Unit.hpp"

class UI {
public:
	void update();
	void drawBackground();
	void drawUnits();
	void drawTerrain();
	void drawForeground();
private:
	int gridX, gridY;
	int scrollOffsetX = 0;
	int scrollOffsetY = 0;
	enum selectionType { none = 0, unit, ability };
	selectionType selectionLevel = none;
	unitID unitSelected;
	string abilitySelected;
	int abilitySelectionPosition;
};

extern std::unique_ptr<UI> ui;

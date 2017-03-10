#pragma once
#include "Unit.hpp"

class UI {
public:
	UI();
	void update();
	void drawBackground();
	void drawForeground();
private:
	int gridX, gridY;
	int scrollOffsetX, scrollOffsetY;
	enum selectionType { none = 0, unit, ability };
	selectionType selectionLevel; //0 = top, 1 = unit selected, 2 = ability selected
	unitID unitSelected = 0;
	string abilitySelected = "";
};

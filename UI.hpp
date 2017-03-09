#pragma once
class UI {
public:
	void update();
	void draw_grid();
private:
	int gridX, gridY;
	enum selectionType { none = 0, unit, ability };
	selectionType selectionLevel; //0 = top, 1 = unit selected, 2 = ability selected
	int unitSelected = 0;
	string abilitySelected = "";
};

#pragma once
#include <vector>
#include "FL/Fl_Color_Chooser.H"

class Star {
public:
	Star() :color(0), pickup(false) {}
	Star(unsigned int _color, bool _pickup);
	unsigned int getColor();
	bool getPickup();
	void setColor(unsigned int _color);
	void setPickup(bool _pickup);
private:
	unsigned int color;
	bool pickup;
};

typedef std::vector<Star> Stars;
class Starmat : public std::vector<Stars> {
public:
	Starmat() {}
	Starmat(int _row, int _col);
};
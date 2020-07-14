#pragma once
#include <vector>
#include "FL/Fl_Color_Chooser.H"

class Star {
public:
	Star() :color(0), pickup(false) {}
	Star(unsigned int _color, bool _pickup);
private:
	unsigned int color;
	bool pickup;
};

typedef std::vector<Star> Stars;
class Starmat : public std::vector<Stars> {
public:
	Starmat() :row(0), col(0) {}
	Starmat(int _row, int _col);
	Star getStar(int _row, int _col);
	void setStar(int _row, int _col, Star _star);
private:
	int row, col;
};
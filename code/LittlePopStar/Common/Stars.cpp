#include "Stars.h"

Star::Star(unsigned int _color, bool _pickup) : color(_color), pickup(_pickup) {}

unsigned int Star::getColor() {
	return color;
}

bool Star::getPickup() {
	return pickup;
}

void Star::setColor(unsigned int _color) {
	color = _color;
}

void Star::setPickup(bool _pickup) {
	pickup=_pickup;
}

Starmat::Starmat(int _row, int _col) {
	this->resize(_row);
	for (int i = 0; i < _row; ++i)
		(*this)[i].resize(_col);
}

Star Starmat::getStar(int _row, int _col) {
	return (*this)[_row][_col];
}

void Starmat::setStar(int _row, int _col, Star _star) {
	(*this)[_row][_col] = _star;
}


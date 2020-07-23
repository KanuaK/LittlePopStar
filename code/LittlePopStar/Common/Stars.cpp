#include "Stars.h"

Star::Star(unsigned int _color, bool _pickup) : color(_color), pickup(_pickup) {}

unsigned int Star::getColor() const {
	return color;
}

bool Star::getPickup() const {
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

const Star& Starmat::getStar(int _row, int _col) const {
	return (*this)[_row][_col];
}

Star& Starmat::setStar(int _row, int _col) {
	return (*this)[_row][_col];
}


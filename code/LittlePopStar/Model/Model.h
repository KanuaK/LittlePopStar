#pragma once
#include "../Common/Stars.h"

class StarMap {
	Starmat starMap;
	
public:
	int row, col;
	unsigned int colorNum;
	StarMap(int _row, int _col,unsigned int _colorNum);
	void initStars();
	void pickupStar(int _row, int _col);
	void pickupStar(int _num);

};
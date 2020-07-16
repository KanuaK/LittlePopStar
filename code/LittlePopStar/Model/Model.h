#pragma once
#include "../Common/Stars.h"
#include <functional>
#include <memory>
class StarMap {
	Starmat starMap;
	std::function<void(int)> sendNotification;//fire
public:
	int row, col;
	unsigned int colorNum;
	StarMap(int _row, int _col,unsigned int _colorNum);
	void initStars();
	bool pickupStar(int _row, int _col);
	bool pickupStar(int _num);
	void attachNotification(std::function<void(int)>);
	void detachNotification();
	std::shared_ptr<Starmat> getStarmat();
};
#pragma once
#include "../Common/Stars.h"
#include <functional>
#include <memory>
class StarMap {
public:
	int row, col;
	unsigned int colorNum;
	StarMap(int _row, int _col,unsigned int _colorNum);
	void initStars();
	bool pickupStar(int _row, int _col);
	bool pickupStar(int _num);
	void pickdownStar(); //set pickup=false for all stars
	bool checkGameOver(); //check if game is over(No star exists or no star can be eliminated)
	void popStar(); //eliminate all stars picked up
	void attachNotification(std::function<void(int)>&&);
	//void detachNotification();
	Starmat* getStarmat();
private:
	Starmat starMap;
	std::function<void(int)> sendNotification;//fire
};
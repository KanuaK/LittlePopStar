#pragma once
#include "../Common/Stars.h"
#include <functional>
#include <memory>
#include <string>
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
	bool popStar(); //eliminate all stars picked up
	void attachNotification(std::function<void(int)>&&);
	bool load(const std::string&);
	bool save(const std::string&);
	//void detachNotification();
	std::function<Starmat* ()> getStarmatFunc();
	std::function<std::vector<std::pair<int,int>>*()> getPopVecFunc();
	int* getScore();
	Starmat* getStarmat();
private:
	Starmat starMap;
	int score;
	std::vector<std::pair<int,int>> popVec;
	std::function<void(int)> sendNotification;//fire
};
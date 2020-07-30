#pragma once
#include "../Model/Model.h"
#include "../Common/Stars.h"
#include <functional>
#include <memory>
class StarMapVM {
public:
	StarMapVM();
	void attachNotification(std::function<void(int)>);//add notification
	void detachNotification();
	void attachModel(StarMap*);
	std::shared_ptr<StarMap> detachModel();
	std::function<void(int)> getNotification();//void receiveNotification(int);
	std::function<bool(int, int)> getPickupCommand();
	std::function<void()> getRestartCommand(); //return a function that will reset the StarMap
	std::function<bool(const std::string&)> getLoadCommand();
	std::function<bool(const std::string&)> getSaveCommand();
	//properties
	std::function<Starmat* ()> getStarmatFunc();
	Starmat* getStarmat();
	int* getScore();
	int getRow();
	int getCol();
	std::function<std::vector<std::pair<int, int>>* ()> getPopVecFunc();
private:
	StarMap* m_refModel;
	std::function<void(int)> sendNotification;//fire
};
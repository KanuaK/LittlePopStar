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

	//properties
	std::shared_ptr<Starmat> getStarmat();
private:
	StarMap* m_refModel;
	std::function<void(int)> sendNotification;//fire
};
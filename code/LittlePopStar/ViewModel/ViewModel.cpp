#include "ViewModel.h"
#include <utility>

StarMapVM::StarMapVM() {}

void StarMapVM::attachNotification(std::function<void(int)> _notification_func) {
	sendNotification = _notification_func;
}

void StarMapVM::detachNotification() {
	sendNotification = std::function<void(int)>();
}

std::function<void(int)> StarMapVM::getNotification() {
	return [this](int uID) {
			//puts("notification in model");
			this->sendNotification(uID);
			//uID = 0 Star info changed
			//      1 gameOver 
	};
}

void StarMapVM::attachModel(StarMap* refModel) {
	m_refModel = refModel;
}

std::shared_ptr<StarMap> StarMapVM::detachModel() {
	return std::shared_ptr<StarMap>(std::move(m_refModel));
}

Starmat* StarMapVM::getStarmat() {
	return m_refModel->getStarmat();
}

int* StarMapVM::getScore() {
	return m_refModel->getScore();
}

const std::vector<Star>& StarMapVM::getPopVec() {
	return m_refModel->getPopVec();
}

#include "../../model/Model.h"
#include "../ViewModel.h"
std::function<void()> StarMapVM::getRestartCommand() {
	return [this]()->bool {
		this->m_refModel->initStars();
		return;
	};
}
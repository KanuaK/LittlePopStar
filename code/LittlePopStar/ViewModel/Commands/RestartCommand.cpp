#include "../../model/Model.h"
#include "../ViewModel.h"
std::function<void()> StarMapVM::getRestartCommand() {
	return [this]()->void {
		this->m_refModel->initStars();
		return;
	};
}
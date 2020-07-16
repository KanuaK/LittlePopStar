#include "../../model/Model.h"
#include "../ViewModel.h"
std::function<bool(int, int)> StarMapVM::getPickupCommand() {
	return [this](int _row, int _col)->bool {
		return this->m_refModel->pickupStar(_row, _col);
	};
}
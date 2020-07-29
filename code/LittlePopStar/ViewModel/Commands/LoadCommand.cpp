#include "../../model/Model.h"
#include "../ViewModel.h"
std::function<bool(const std::string&)> StarMapVM::getLoadCommand() {
	return [this](const std::string& fileName)->bool {
		return this->m_refModel->load(fileName);
	};
}
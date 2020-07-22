#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Enumerations.H>

#include <functional>
#include <memory>
#include <utility>

#include "StarMapView.h"
#include "../Common/Stars.h"
#include <iostream>

int ColorMap[8] = { 88, 63, 95, 216, 248, 223, 255, 56 };	//maps the integer values stored in the star objects of the model to default FLTK colour values
//red, green, yellow, blue, magenta, cyan, white, black

StarMapView::StarMapView(int _rows, int _cols) : m_rows(_rows), m_cols(_cols), Fl_Group(0, 0, _cols* STAR_BUTTON_DIMENSION, _rows* STAR_BUTTON_DIMENSION, 0){
	end();
	initialize();
};

StarMapView::~StarMapView() {
	return;
}

void StarMapView::attachModel(StarMap* _refModel) {
	m_refModel = _refModel;
}

std::shared_ptr<StarMap> StarMapView::detachModel() {
	return std::shared_ptr<StarMap>(std::move(m_refModel));
}

void StarMapView::attach_PickupCommand(std::function<bool(int, int)>&& cf) {
	m_cmdPickup = std::move(cf);
}

std::function<bool(int, int)> StarMapView::detach_PickupCommand() {
	return std::function<bool(int, int)>(std::move(m_cmdPickup));
}

void StarMapView::pickup_cb(Fl_Widget* Bp, void* v)
{
	std::function<void(int, int)>& cmdFunc = *((std::function<void(int, int)>*)v);
	if (cmdFunc != nullptr) {
		cmdFunc(Bp->y()/STAR_BUTTON_DIMENSION, Bp->x()/STAR_BUTTON_DIMENSION);
	}
	return;
}

void StarMapView::initialize() {
	for (int row = 0; row < m_rows; row++) {
		for (int col = 0; col < m_cols; col++) {
			Fl_Widget* temp = new Fl_Button(col * STAR_BUTTON_DIMENSION, row * STAR_BUTTON_DIMENSION, STAR_BUTTON_DIMENSION, STAR_BUTTON_DIMENSION, "*");
			temp->callback((Fl_Callback*) &pickup_cb, &m_cmdPickup);
			temp->labelsize(STAR_BUTTON_DIMENSION / 4);
			add(temp);
		}
	}
	if (children() != m_rows * m_cols)	throw "Initialization Failed";
	return;
}

void StarMapView::update() {
	std::shared_ptr<Starmat> starMat = m_refModel->getStarmat();
	Fl_Widget* currentButton;
	Star* currentStar;

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			currentButton = child(i*m_cols + j);
			currentStar = &(starMat->getStar(i, j));
			if (!currentStar->getPickup()) {	//if star has not yet been picked up
				currentButton->color(ColorMap[currentStar->getColor()]);	//update button colour to the value stored in the model
				currentButton->labelcolor(ColorMap[(currentStar->getColor()+1)%8]);
			}
			else {	//star has been picked up	
				currentButton->color(FL_GRAY);	//set button color to grey
				currentButton->label(0);	//remove the star
			}
		}
	}
	redraw();
	return;
}

std::function<void(int)> StarMapView::getNotification() {
	return [this](int uID) {
		if (uID == 0)	this->update();
	};
}

StarButton::StarButton(	int _row, int _col) : m_row(_row), m_col(_col),
						Fl_Button(_row* STAR_BUTTON_DIMENSION, _col* STAR_BUTTON_DIMENSION, STAR_BUTTON_DIMENSION, STAR_BUTTON_DIMENSION, "*") {
}
//does not set callback at construction

StarButton::~StarButton() {
	return;
}
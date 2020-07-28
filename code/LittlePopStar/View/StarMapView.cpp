#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_draw.H>

#include <functional>
#include <memory>
#include <utility>

#include <string>

#include "StarMapView.h"
#include "../Common/Stars.h"
#include <iostream>

const int colorNum = 8;
int ColorMap[colorNum] = { 88, 63, 95, 216, 248, 223, 255, 56 };	//maps the integer values stored in the star objects of the model to default FLTK colour values
//red, green, yellow, blue, magenta, cyan, white, black
const std::string assetFolder = { "Assets/" };	//based on the location of main.cpp
const std::string assetLocations[colorNum] = {"blueStar.png", "greenStar.png", "redStar.png", "yellowStar.png", "purpleStar.png", "orangeStar.png", "pinkStar.png", "whiteStar.png"};

StarMapView::StarMapView(int _rows, int _cols) : m_rows(_rows), m_cols(_cols), Fl_Group(0, MENU_BAR_HEIGHT, _cols * STAR_BUTTON_DIMENSION, _rows* STAR_BUTTON_DIMENSION, 0){
	end();
	std::string location;
	for (int i = 0; i < colorNum; i++) {
		location = assetFolder + assetLocations[i];
		//std::cout << location << std::endl;
		Fl_PNG_Image fullSizeTexture(location.c_str());
		m_starTextures.push_back(fullSizeTexture.copy(STAR_BUTTON_DIMENSION*3/4, STAR_BUTTON_DIMENSION*3/4));
	}
	initialize();
}

StarMapView::~StarMapView() {
	for (int i = 0; i < m_starTextures.size(); i++)	delete(m_starTextures[i]);
	return;
}

void StarMapView::attachStarmat(Starmat* _refStarmat) {
	m_refStarmat = _refStarmat;
}

//std::shared_ptr<StarMap> StarMapView::detachModel() {
//	return std::shared_ptr<StarMap>(std::move(m_refModel));
//}

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
	Fl_Widget* temp;
	Fl_Color backgroundColor = fl_rgb_color(200, 191, 231);
	for (int row = 0; row < m_rows; row++) {
		for (int col = 0; col < m_cols; col++) {
			temp = new Fl_Button(col * STAR_BUTTON_DIMENSION, row * STAR_BUTTON_DIMENSION, STAR_BUTTON_DIMENSION, STAR_BUTTON_DIMENSION, "");
			temp->callback((Fl_Callback*) &pickup_cb, &m_cmdPickup);
			temp->align(FL_ALIGN_INSIDE|FL_ALIGN_BOTTOM);//FL_ALIGN_IMAGE_OVER_TEXT);
			temp->labelsize(0);//_FL_IMAGE_LABEL);
			temp->color(backgroundColor, backgroundColor);
			add(temp);
		}
	}
	if (children() != m_rows * m_cols)	throw "Initialization Failed";
	return;
}

void StarMapView::update() {
	Fl_Widget* currentButton;
	const Star* currentStar;

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			currentButton = child(i*m_cols + j);
			currentStar = &(m_refStarmat->getStar(i, j));
			if (currentStar->getColor() == 0)	currentButton->image((Fl_Image*)0);
			else currentButton->image(m_starTextures[(currentStar->getColor()) % 8]);
			if (!currentStar->getPickup()) {	//if star has not yet been picked up
				currentButton->box(FL_UP_BOX);
			}
			else {	//star has been picked up	
				//currentButton->color(FL_GRAY);	//set button color to grey
				//currentButton->label(0);	//remove the star
				currentButton->box(FL_DOWN_BOX);
			}
			//std::cout << currentButton->box();
		}
	}
	redraw();
	return;
}

int StarMapView::gameOver() {
	update();
	Fl_Window gameOverMessage(STAR_BUTTON_DIMENSION*4, STAR_BUTTON_DIMENSION*2, "Game Over");
	Fl_Box b(0, 0, STAR_BUTTON_DIMENSION * 4, STAR_BUTTON_DIMENSION * 2, "Game Over!");
	b.labelfont(FL_HELVETICA_BOLD);
	b.labelsize(20);
	gameOverMessage.end();
	gameOverMessage.show();
	return Fl::run();
}

std::function<void(int)> StarMapView::getNotification() {
	return [this](int uID) {
		if (uID == 0)	this->update();
		else if (uID == 1)	this->gameOver();
	};
}

StarButton::StarButton(	int _row, int _col) : m_row(_row), m_col(_col),
						Fl_Button(_row* STAR_BUTTON_DIMENSION, _col* STAR_BUTTON_DIMENSION, STAR_BUTTON_DIMENSION, STAR_BUTTON_DIMENSION, "*") {
	type(1);
}
//does not set callback at construction

StarButton::~StarButton() {
	return;
}
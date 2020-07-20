#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Enumerations.H>
#include <functional>
#include <memory>

#include "../Model/Model.h"

int ColorMap[8] = { 88, 63, 95, 216, 248, 223, 255, 56 };	//maps the integer values stored in the star objects of the model to default FLTK colour values
//red, green, yellow, blue, magenta, cyan, white, blacks

class StarMapView : public Fl_Group{
public:
	StarMapView(int _rows, int _cols, int _colorNum);
	StarMapView(const StarMapView&) = delete;	//do not automatically define copy constructor
	StarMapView& operator=(const StarMapView&) = delete;	//do not automatically defince assignment operator
	~StarMapView();

	void attachModel(const std::shared_ptr<StarMap>&);	//link the model so that it can be accessed to update the view
	std::shared_ptr<StarMap> detachModel();	//delink the model


	void attach_PickupCommand(std::function<bool(int, int)>&& cf);	//assign a function to the the pickup command stored in m_cmdPickup. the arguement passed will be provided by the getPickupCommand of the view model 
	std::function<bool(int, int)> detach_PickupCommand();	//overwrite the pickup command stored in m_cmdPickup.

	void update(int uID);	//updates the view to the values stored in the model. this is the function that should be assigned to StarMapVM.sendNotification

private:
	void initialize();	//initialize StarMapView, including adding a button widget to the array of children widgets for each star in the model

	std::function<bool(int, int)> m_cmdPickup;

	int m_rows, m_cols;
	unsigned int m_colorNum;
	std::shared_ptr<StarMap> m_refModel;
};

class StarButton : public Fl_Button{	//has no externel references
public:
	StarButton(int _row, int _col, int _color, int _pushed);
	StarButton(const StarButton&) = delete;	//do not automatically define copy constructor
	StarButton& operator=(const StarButton&) = delete;	//do not automatically define copy constructor
	~StarButton();
	//unfinished
};
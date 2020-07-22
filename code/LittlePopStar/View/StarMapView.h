#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Enumerations.H>

#include <functional>
#include <memory>

#include "../Model/Model.h"

const int STAR_BUTTON_DIMENSION = 100;	//used to determine the dimension of the StarButton objects in the view

class StarButton : public Fl_Button {
public:
	StarButton(int _row, int _col);
	StarButton(const StarButton&) = delete;	//do not automatically define copy constructor
//	StarButton& operator=(const StarButton&) = delete;	//do not automatically define equals operator
	~StarButton();

private:
	const int m_row, m_col;
};
	
class StarMapView : public Fl_Group{
public:
	StarMapView(int _rows, int _cols);
	StarMapView(const StarMapView&) = delete;	//do not automatically define copy constructor
	StarMapView& operator=(const StarMapView&) = delete;	//do not automatically defince assignment operator
	~StarMapView();

	void attachModel(const std::shared_ptr<StarMap>&);	//link the model so that it can be accessed to update the view
	std::shared_ptr<StarMap> detachModel();	//delink the model

	void attach_PickupCommand(std::function<bool(int, int)>&& cf);
	std::function<bool(int, int)> detach_PickupCommand();

	void update(int uID);	//updates the view to the values stored in the model. this is the function that should be assigned to StarMapVM.sendNotification

private:
	void initialize();	//initialize StarMapView, including adding a button widget to the array of children widgets for each star in the model

	static void pickup_cb(Fl_Widget* pW, void* pD);

	std::function<bool(int, int)> m_cmdPickup;	//takes as arguements the row and col of the StarButton that was picked up

	const int m_rows, m_cols;
	std::shared_ptr<StarMap> m_refModel;
};
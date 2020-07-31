#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>

#include <functional>
#include <memory>
#include <vector>
#include <utility>

#include "../Common/Stars.h"

const int STAR_BUTTON_DIMENSION = 100;	//used to determine the dimension of the StarButton objects in the view
const int MENU_BAR_HEIGHT = 25;

class StarMapView : public Fl_Group{
public:
	//constructor, destructor, default generated functions
	StarMapView(int _rows, int _cols);
	StarMapView(const StarMapView&) = delete;	//do not automatically define copy constructor
	StarMapView& operator=(const StarMapView&) = delete;	//do not automatically defince assignment operator
	~StarMapView();

	//attach links
	void attachStarmat(Starmat*);	//link the model so that it can be accessed to update the view
	void attachPopVecFunct(std::function<std::vector<std::pair<int, int>>* ()>&& f);
	void attach_PickupCommand(std::function<bool(int, int)>&& cf);

	//notification that the view should be updated
	void updateDriver(int uID);

	void reinitialize(int _rows, int _cols);

	int gameOverFlag;

private:
	void initialize();	//initialize StarMapView, including adding a button widget to the array of children widgets for each star in the model

	//functions called by update driver declared in get notification, depending on status
	static void popAnimation(void* v);
	void update();
	int gameOver(int score);
	void getPopVec();	//updates pop vector
	
	//button callback handler
	static void pickup_cb(Fl_Widget* pW, void* pD);

	//button callback arguement
	std::function<bool(int, int)> m_cmdPickup;	//takes as arguements the row and col of the StarButton that was picked up
	std::function<std::vector<std::pair<int, int>>* ()> m_getPopVecFunct;

	//image assets
	std::vector<Fl_Image*> m_starTextures;
	
	//vectir containing the starts which will be popped during a given view update
	std::vector<std::pair<int, int>>* m_popVec;

	//game instance dimensions
	int m_rows, m_cols;

	//common level starmat. contains information of the current game state
	Starmat* m_refStarmat;
};
#pragma once

#include <FL/FL.H>
#include <FL/FL_Window.H>
#include <FL/Fl_Menu_Bar.H>

#include "../View/StarMapView.h"

class MainWindow : public Fl_Window {
public:

	MainWindow(int _rows, int _cols);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	~MainWindow();

	StarMapView& get_StarMapView();

private:

	StarMapView m_starMapView;
	//Fl_Menu_Bar m_menuBar;
};
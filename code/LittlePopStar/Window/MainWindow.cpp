#include <FL/FL.H>
#include <FL/FL_Window.H>
#include <FL/Fl_Menu_Bar.H>

#include "../View/StarMapView.h"
#include "../Window/MainWindow.h"

#include <functional>

MainWindow::MainWindow(int _rows, int _cols) :	Fl_Window(_cols * STAR_BUTTON_DIMENSION, _rows* STAR_BUTTON_DIMENSION, "LittlePopStar"), 
												m_starMapView(_rows, _cols) {
	end();
	resizable(m_starMapView);
}

MainWindow::~MainWindow() {
	return;
}

StarMapView& MainWindow::get_StarMapView() {
	return m_starMapView;
}
#include <FL/FL.H>
#include <FL/FL_Window.H>
#include <FL/Fl_Menu_Bar.H>

#include "../View/StarMapView.h"
#include "../Window/MainWindow.h"

#include <functional>

MainWindow::MainWindow(int _rows, int _cols) :	Fl_Window(_cols * STAR_BUTTON_DIMENSION, _rows* STAR_BUTTON_DIMENSION + MENU_BAR_HEIGHT, "LittlePopStar"),
												m_starMapView(_rows, _cols), m_menuBar(0, 0, _cols* STAR_BUTTON_DIMENSION, MENU_BAR_HEIGHT, "Menu"){
	end();
	m_menuBar.add("Restart...", 0, (Fl_Callback*) &restart_cb, &m_cmdRestart);
	resizable(m_starMapView);
}

MainWindow::~MainWindow() {
	return;
}

StarMapView& MainWindow::get_StarMapView() {
	return m_starMapView;
}

void MainWindow::attach_RestartCommand(std::function<void()>&& cf) {
	m_cmdRestart = std::move(cf);
}

void MainWindow::restart_cb(Fl_Widget* Wp, void* v) {
	std::function<void()>& cmdFunc = *((std::function<void()>*)v);
	if (cmdFunc != nullptr) {
		cmdFunc();
	}
}
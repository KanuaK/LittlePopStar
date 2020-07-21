#include <FL/FL.H>
#include <FL/FL_Window.H>
#include <FL/Fl_Menu_Bar.H>

#include "StarMapView.h"
#include "MainWindow.h"

#include <functional>

MainWindow::MainWindow(int _rows, int _cols) :	Fl_Window(_cols* STAR_BUTTON_DIMENSION, _rows* STAR_BUTTON_DIMENSION, "LittlePopStar"), 
												m_starMapView(_rows, _cols) {
	end();
	callback((Fl_Callback*)&close_cb, &m_cmdClose);
	resizable(m_starMapView);
}

MainWindow::~MainWindow() {
	return;
}

const StarMapView& MainWindow::get_StarMapView() {
	return m_starMapView;
}

void MainWindow::attach_CloseCommand(std::function<void()>&& cf) {
	m_cmdClose = std::move(cf);
	return;
}
std::function<void()> MainWindow::detach_CloseCommand() {
	return std::function<void()>(std::move(m_cmdClose));
}

void MainWindow::close_cb(Fl_Window* pW, void* pD) {
	std::function<void()>& cf = *((std::function<void()>*)pD);
	if (cf != nullptr)
		cf();
	default_callback(pW, pD);
	return;
}
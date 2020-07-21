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

	const StarMapView& get_StarMapView();

	void attach_CloseCommand(std::function<void()>&& cf);
	std::function<void()> detach_CloseCommand();

private:
	static void close_cb(Fl_Window* pW, void* pD);

	std::function<void()> m_cmdClose;

	StarMapView m_starMapView;
	//Fl_Menu_Bar m_menuBar;
};
#pragma once

#include <FL/FL.H>
#include <FL/FL_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include "StarMapView.h"

class MainWindow : public Fl_Window {
public:

	MainWindow(int w, int h, const char* t);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	~MainWindow();

	StarMapView& get_StarMapView();

	void attach_CloseCommand(std::function<void()>&& cf) noexcept;
	std::function<void()> detach_CloseCommand() noexcept;

private:
	static void close_cb(Fl_Window* pW, void* pD);

	std::function<void()> m_cmdClose;

	StarMapView m_starMapView;
	Fl_Menu_Bar m_menuBar;
};
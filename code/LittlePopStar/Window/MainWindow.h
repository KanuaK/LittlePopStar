#pragma once

#include <FL/FL.H>
#include <FL/FL_Window.H>
#include <FL/Fl_Menu_Bar.H>

#include <string>

#include "../View/StarMapView.h"

class MainWindow : public Fl_Window {
public:

	MainWindow(int _rows, int _cols);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	~MainWindow();

	StarMapView& get_StarMapView();

	void attach_RestartCommand(std::function<void()>&& cf);
	void attach_LoadCommand(std::function<bool(const std::string&)>&& cf);
	void attach_SaveCommand(std::function<bool(const std::string&)>&& cf);

	static void restart_cb(Fl_Widget* Wp, void* v);
	static void load_cb(Fl_Widget* Wp, void* v);
	static void save_cb(Fl_Widget* Wp, void* v);

private:

	std::function<void()> m_cmdRestart;
	std::function<bool(const std::string&)> m_cmdLoad;
	std::function<bool(const std::string&)> m_cmdSave;

	StarMapView m_starMapView;
	Fl_Menu_Bar m_menuBar;
};
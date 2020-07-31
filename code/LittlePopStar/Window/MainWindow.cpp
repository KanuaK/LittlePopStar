#include <FL/FL.H>
#include <FL/FL_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Input.H>

#include "../View/StarMapView.h"
#include "../Window/MainWindow.h"

#include <functional>

MainWindow::MainWindow(int _rows, int _cols) :	Fl_Window(_cols * STAR_BUTTON_DIMENSION, _rows* STAR_BUTTON_DIMENSION + MENU_BAR_HEIGHT, "LittlePopStar"), m_starMapView(_rows, _cols), m_menuBar(0, 0, _cols* STAR_BUTTON_DIMENSION, MENU_BAR_HEIGHT, "Menu"){
	end();
	m_menuBar.add("New Game", 0, (Fl_Callback*) &restart_cb, &m_cmdRestart);
	m_menuBar.add("Load", 0, (Fl_Callback*)&load_cb, &m_cmdLoad);
//	m_menuBar.add("Save", 0, (Fl_Callback*)&save_cb, &m_cmdSave);
	m_viewModel = 0;
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

void MainWindow::attach_LoadCommand(std::function<bool(const std::string&)>&& cf) {
	m_cmdLoad = std::move(cf);
}

void MainWindow::attach_SaveCommand(std::function<bool(const std::string&)>&& cf) {
	m_cmdSave = std::move(cf);
}

void MainWindow::attach_viewModel(StarMapVM* vm) {
	m_viewModel = vm;
}

void MainWindow::restart_cb(Fl_Widget* Wp, void* v) {
	//Fl_Window win(400, 100, "Game Size");
	//Fl_Input xInput(50, 25, 100, 25, "Column Number");
	//Fl_Input yInput(250, 25, 100, 25, "Row Number");
	//win.end();
	//win.show();
	std::function<void()>& cmdFunc = *((std::function<void()>*)v);
	if (cmdFunc != nullptr) {
		cmdFunc();
	}
}

void MainWindow::load_cb(Fl_Widget*, void* v)
{
	Fl_Native_File_Chooser fileBrowser;
	fileBrowser.title("Select Load File");
	fileBrowser.type(Fl_Native_File_Chooser::BROWSE_FILE);
	if (fileBrowser.show() == 0) {
		std::function<bool(const std::string&)>& cmdFunc = *((std::function<bool(const std::string&)>*)v);
		if (cmdFunc != nullptr && !cmdFunc((std::string(fileBrowser.filename())))) {
			fl_alert("The selected file cannot be loaded.");
		}
	}
	return;
}

void MainWindow::save_cb(Fl_Widget*, void* v)
{
	Fl_Native_File_Chooser fileBrowser;
	fileBrowser.title("Select Save Location");
	fileBrowser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
	if (fileBrowser.show() == 0) {
		std::function<bool(const std::string&)>& cmdFunc = *((std::function<bool(const std::string&)>*)v);
		if (cmdFunc != nullptr && !cmdFunc(std::string(fileBrowser.filename()))) {
			fl_alert("The game data cannot be saved to the selected location.");
		}
	}
	return;
}

void MainWindow::getStarmat() {
	m_starMapView.attachStarmat(m_viewModel->getStarmat());
}

std::function<void(int)> MainWindow::getNotification() {
	return [this](int uID) {
		if (uID < 0) {
			int rows = m_viewModel->getRow();
			int cols = m_viewModel->getCol();
			this->size(cols * STAR_BUTTON_DIMENSION, rows * STAR_BUTTON_DIMENSION + MENU_BAR_HEIGHT);
			m_starMapView.reinitialize(rows, cols);
			this->getStarmat();
//			redraw();
		}
		m_starMapView.updateDriver(uID);
	};
}
#include "App.h"
#include <memory>
#include "../Model/Model.h"

#include <iostream>

GameApp::GameApp() : m_model(5, 5, 4), m_wndMain(5, 5) {
	//binding
	m_viewmodel.attachModel(&m_model);
	m_model.attachNotification(m_viewmodel.getNotification());
	m_viewmodel.attachNotification(m_wndMain.getNotification());
	//properties
	m_wndMain.attach_viewModel(&m_viewmodel);
	//m_wndMain.get_StarMapView()->attachStarmat(m_model.getStarmat());
	//m_wndMain.get_StarMapView().update();
	
	//commands
	m_wndMain.get_StarMapView()->attach_PickupCommand(m_viewmodel.getPickupCommand());
	m_wndMain.get_StarMapView()->attachPopVecFunct(m_viewmodel.getPopVecFunc());
	m_wndMain.attach_RestartCommand(m_viewmodel.getRestartCommand());
	m_wndMain.attach_LoadCommand(m_viewmodel.getLoadCommand());
	//m_wndMain.attach_SaveCommand(nullptr);

	//notifications

	/// m_viewmodel.attachNotification(m_wndMain.getNotification());
	
	
}

GameApp::~GameApp() noexcept {}

MainWindow& GameApp::GetMainWindow() noexcept {
	return m_wndMain;
}

int GameApp::Run() {
	m_wndMain.show();
	return Fl::run();
}
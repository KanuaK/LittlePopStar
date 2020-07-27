#include "App.h"
#include <memory>
#include "../Model/Model.h"

GameApp::GameApp() : m_model(5, 5, 4), m_wndMain(5, 5) {
	//binding
	m_viewmodel.attachModel(&m_model);
	m_model.attachNotification(m_viewmodel.getNotification());
	m_viewmodel.attachNotification(m_wndMain.get_StarMapView().getNotification());
	//properties
	m_wndMain.get_StarMapView().attachStarmat(m_model.getStarmat());
	m_wndMain.get_StarMapView().update();
	
	//commands
	m_wndMain.get_StarMapView().attach_PickupCommand(m_viewmodel.getPickupCommand());

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
#pragma once
/////////////////////////////////////////////////

#include "../Model/Model.h"
#include "../ViewModel/ViewModel.h"
#include "../window/MainWindow.h"


	// TextPart

class GameApp {
public:
	GameApp();
	GameApp(const GameApp&) = delete;
	GameApp& operator=(const GameApp&) = delete;
	~GameApp() noexcept;

public:
	MainWindow& GetMainWindow() noexcept;
	int Run();
private:
	StarMap      m_model;
	StarMapVM    m_viewmodel;
	MainWindow     m_wndMain;
};


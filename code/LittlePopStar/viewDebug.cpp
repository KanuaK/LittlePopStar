#include "View/StarMapView.h"
#include "Window/MainWindow.h"

#include <Fl/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Group.H>

#include <functional>
#include <memory>
#include <utility>

#include <iostream>

void test(int x, int y) {
	std::cout << x << ", " << y << std::endl;
	return;
}

//int main(int argc, char* argv[]) {
//	MainWindow* win;
//	StarMap* model = new StarMap(5, 5, 5);
//	win = new MainWindow(5, 5);
//	win->get_StarMapView().attachModel(std::shared_ptr<StarMap>(model));
//	win->get_StarMapView().update(0);
//	win->get_StarMapView().attach_PickupCommand(std::function<void(int, int)>(test));
//	std::cout << "hi";
//	win->show();
//	return  Fl::run();
//}
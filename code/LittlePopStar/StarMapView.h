#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Enumerations.H>

class StarMapView : public Fl_Window {
public:
	view();
	view(int _rows, int _cols, int _colorCount);

private:
	int row, col;
	unsigned int colorNum;
};
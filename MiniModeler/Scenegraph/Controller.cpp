#include "Controller.h"

Controller::Controller(int x, int y, int w, int h) :Fl_Window(x, y, w, h, "Extrudor"){
	win = new cubeWin(x, y, w, h);
	win->show();
	this->end();
}

#ifndef DISPLAY_H
#define DISPLAY_H
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Hold_Browser.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Value_Slider.H>
#ifndef CUBEWIN
#define CUBEWIN
#include "cubeWin.h"
#endif


class Controller : public Fl_Window{
private:			// the OpenGL window
public:
	cubeWin* win;
	Controller(int x, int y, int w, int h);				// constructor
	~Controller(){ free(win); };
};


#endif

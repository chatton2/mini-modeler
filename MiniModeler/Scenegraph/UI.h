#include <string>
#include <map>
#include <utility>
#include <list>
#include <FL/Fl.H>		
#include <FL/Fl_Tree.H>
#include <FL/Fl_Tree_Item.H>
#include <FL/Fl_Tree_Prefs.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Button.H>	
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Input.H>	
#include <FL/Fl_Progress.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Check_Button.H>
#include <iostream>
#include <string.h>
#include <iostream>
#include <jpeg/jpeglib.h>
#include <jpeg/jerror.h>
#include <sstream>
#include "Controller.h"
#include "flatView.h"

class UI :public Fl_Window  // subclass of Fl_Gl_Window
{
private:
	// method in FL_GL_Window class
public:
	int rowNum;
	int colNum;
	double width;
	double depth;
	double r;
	double g;
	double b;
	Fl_Window* startWin;
	Fl_Window* subWin;
	Fl_Spinner* subSpin;
	Fl_Button* smoothiB;
	Fl_Spinner* rowSpin;
	Fl_Spinner* colSpin;
	Fl_Spinner* widthSpin;
	Fl_Spinner* depthSpin;
	Fl_Color_Chooser* colorP;
	Fl_Button* start;
	Fl_Button* topB;
	Fl_Button* frontB;
	Fl_Button* bonusB;
	Fl_Button* gridB;
	Fl_Button* transformB;
	cubeWin* myWindow;
	flatView* topDown;
	Fl_Button* colorB;
	Fl_Spinner* xSpin;
	Fl_Spinner* ySpin;
	Fl_Counter* zSpin;
	Fl_Slider* capSpin;
	Controller* control;

	UI(int x, int y);
	~UI();

};

static void startCall(Fl_Widget * w, void* v);
static void transformBCall(Fl_Widget * w, void* v);
static void topBCall(Fl_Widget * w, void* v);
static void frontBCall(Fl_Widget * w, void* v);
static void gridBCall(Fl_Widget * w, void* v);
static void colorBCall(Fl_Widget * w, void* v);
static void smoothiBCall(Fl_Widget * w, void* v);
static void capSpinCall(Fl_Widget * w, void* v);
static void ySpinCall(Fl_Widget * w, void* v);
static void xSpinCall(Fl_Widget * w, void* v);
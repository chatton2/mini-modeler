#include <FL/Fl.H>
#include <FL/Gl.H>
#include <Fl/Fl_Gl_Window.H>
#include <GL/glu.h>
#ifndef HEIGHTFIELD
#define HEIGHTFIELD
#include "heightField.h"
#endif
#include <GL/glut.h> // Include the GLUT header file  
#include "algebra3.h"
#ifndef CAMERA
#define CAMERA
#include "Camera.h"
#endif

class flatView :public Fl_Gl_Window  // subclass of Fl_Gl_Window
{
private:
	int handle(int event);
	void init();
public:
	heightField* myField;
	Camera* cam;
	double selectX;
	double selectY;
	void draw();
	flatView(int x, int y, int w, int h);
	~flatView(){ free(cam); };
};
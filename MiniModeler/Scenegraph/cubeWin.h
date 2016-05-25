#include <FL/Fl.H>
#include <FL/Gl.H>
#include <Fl/Fl_Gl_Window.H>
#include <GL/glu.h>
#include "algebra3.h"
#ifndef HEIGHTFIELD
#define HEIGHTFIELD
#include "heightField.h"
#endif
#ifndef CAMERA
#define CAMERA
#include "Camera.h"
#endif

class cubeWin :public Fl_Gl_Window  // subclass of Fl_Gl_Window
{
private:
	mat4 rot;
	void init();				// initialize the required OpenGL transforms				// draw the faces in the OpenGL window
	int handle(int event);		// handle keyboard events
public:
	Camera* c;					// a pointer to the camera
	int angle;
	heightField* myField;
	static void spinThing(void* j);
	void draw();
	cubeWin(int x, int y, int w, int h);
	~cubeWin(){ free(c); free(myField); };
};
#include "cubeWin.h"


cubeWin::cubeWin(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h){
	c = new Camera(7, 0, 0);	// create a camera
}

void cubeWin::init(){	// initialize the required OpenGL transforms
	glViewport(0, 0, w(), h());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 10);		// experiment with these settings to see their effects
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

void cubeWin::draw(){
	if (!valid()){
		init();				// make sure the OpenGL settings are completed once before drawing
		valid(1);
	}
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec3 bluh = c->getEye();
	vec3 blerk = c->getUp();
	gluLookAt(bluh[0], bluh[1], bluh[2],	// set the camera
		0, 0, 0,
		blerk[0], blerk[1], blerk[2]);
	this->myField->draw();
}


int cubeWin::handle(int event){		// handle keyboard events
	if (event == FL_KEYUP){				// when the key is released, check for an event and handle it
		if (Fl::event_key() == 'a'){
			c->increasePhi(-7);
			redraw();
		}
		if (Fl::event_key() == 'd'){
			c->increasePhi(7);
			redraw();
		}
		if (Fl::event_key() == 'w'){
			c->increaseTheta(-7);
			redraw();
		}
		if (Fl::event_key() == 's'){
			c->increaseTheta(7);
			redraw();
		}
		if (Fl::event_key() == 'e'){
			c->increaseRad(-.5);
			redraw();
		}
		if (Fl::event_key() == 'f'){
			c->increaseRad(.5);
			redraw();
		}
	}
	return Fl_Gl_Window::handle(event);
}
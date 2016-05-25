#include "flatView.h"
#include <iostream>

flatView::flatView(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h){
	cam = new Camera(1, 0, 0);
}


void flatView::draw(){
	double w = myField->rows / 2;
	double d = myField->cols / 2;
	if (!valid()){
		init();				// make sure the OpenGL settings are completed once before drawing
		valid(1);
	}
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vec3 bluh = cam->getEye();
	vec3 blerk = cam->getUp();
	gluLookAt(bluh[0], bluh[1], bluh[2],	// set the camera
		0, 0, 0,
		blerk[0], blerk[1], blerk[2]);
	for (std::list<mat4>::iterator it = this->myField->vertices->begin(); it != this->myField->vertices->end(); it++){
		glBegin(GL_LINE_LOOP);
		if ((*it)[0][0] == (selectX) - d && (*it)[0][1] == (selectY) - w){
			glColor3f(1.0, 1.0, 0.0);
		}
		else{
			glColor3f(1.0, 1.0, 1.0);
		}
		glVertex3f((*it)[0][0] * .3, (*it)[0][1] * .3, 0);
		if ((*it)[1][0] == (selectX) - d && (*it)[1][1] == (selectY) - w){
			glColor3f(1.0, 1.0, 0.0);
		}
		else{
			glColor3f(1.0, 1.0, 1.0);
		}
		glVertex3f((*it)[1][0] * .3, (*it)[1][1] * .3, 0);
		if ((*it)[2][0] == (selectX) - d && (*it)[2][1] == (selectY) - w){
			glColor3f(1.0, 1.0, 0.0);
		}
		else{
			glColor3f(1.0, 1.0, 1.0);
		}
		glVertex3f((*it)[2][0] * .3, (*it)[2][1] * .3, 0);
		if ((*it)[3][0] == (selectX) - d && (*it)[3][1] == (selectY) - w){
			glColor3f(1.0, 1.0, 0.0);
		}
		else{
			glColor3f(1.0, 1.0, 1.0);
		}
		glVertex3f((*it)[3][0] * .3, (*it)[3][1] * .3, 0);
		glEnd();
	}
}

void flatView::init(){	// initialize the required OpenGL transforms
	glViewport(0, 0, w(), h());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 10);		// experiment with these settings to see their effects
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

int flatView::handle(int event){		// handle keyboard events
	if (event == FL_KEYUP){				// when the key is released, check for an event and handle it
		if (Fl::event_key() == 'p'){
			cam->increaseRad(-.1);
			redraw();
		}
		if (Fl::event_key() == 'l'){
			cam->increaseRad(.1);
			redraw();
		}
	}
	return Fl_Gl_Window::handle(event);
}
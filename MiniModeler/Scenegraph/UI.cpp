#include "UI.h"

UI::UI(int x, int y) : Fl_Window(x, y){
	heightField* starty = new heightField(0, 0, 0, 0,0,0,0, 5);
	rowSpin = new Fl_Spinner(540, 25, 40, 24, "Rows");
	rowSpin->range(0,20);
	colSpin = new Fl_Spinner(540, 56, 40, 24, "Columns");
	colSpin->range(0, 20);
	widthSpin = new Fl_Spinner(630, 25, 40, 24, "Width");
	widthSpin->range(0, 10);
	widthSpin->step(.1);
	depthSpin = new Fl_Spinner(630, 56, 40, 24, "Depth");
	depthSpin->range(0, 10);
	depthSpin->step(.1);
	colorP = new Fl_Color_Chooser(495, 119, 165, 123);
	colorP->rgb(0.0, 0.0, 0.0);
	start = new Fl_Button(495, 265, 75, 30, "Draw");
	colorB = new Fl_Button(590, 265, 75, 30, "Color");
	control = new Controller(25, 10, 445, 376);
	control->win->myField = starty;
	topDown = new flatView(495, 310, 175, 160);
	topDown->myField = starty;
	gridB = new Fl_Button(110, 410, 70, 25, "Grid");
	topB = new Fl_Button(30, 410, 70, 25, "Top");
	frontB = new Fl_Button(30, 445, 70, 25, "Front");
	transformB = new Fl_Button(289, 411, 75, 25, "Transform");
	zSpin = new Fl_Counter(380, 411, 80, 24, "Z");
	capSpin = new Fl_Slider(289, 440, 90, 25, "Cap Height");
	capSpin->type(FL_HORIZONTAL);
	capSpin->range(-30, 30);
	capSpin->step(1);
	capSpin->value(2.0);
	bonusB = new Fl_Button(110, 445, 70, 25, "Fractalize");
	xSpin = new Fl_Spinner(205, 411, 50, 24, "X");
	xSpin->value(0);
	ySpin = new Fl_Spinner(205, 441, 50, 24, "Y");
	ySpin->value(0);
	subWin->begin();
	subWin = new Fl_Window(311, 344, 140, 73);
	subSpin = new Fl_Spinner(90, 6, 40, 24, "Subdivisions");
	subWin->end();
	subWin->hide();
	start->callback(startCall, (void*)this);
	transformB->callback(transformBCall, (void*)this);
	topB->callback(topBCall, (void*)this);
	frontB->callback(frontBCall, (void*)this);
	gridB->callback(gridBCall, (void*)this);
	colorB->callback(colorBCall, (void*)this);
	bonusB->callback(smoothiBCall, (void*)this);
	capSpin->callback(capSpinCall, (void*)this);
	xSpin->callback(xSpinCall, (void*)this);
	ySpin->callback(ySpinCall, (void*)this);
}

UI::~UI(){
	free(startWin);
	free(rowSpin);
	free(colSpin);
	free(widthSpin);
	free(depthSpin);
	free(colorP);
	free(start);
	free(topB);
	free(frontB);
	free(bonusB);
	free(gridB);
	free(transformB);
	free(myWindow);
	free(xSpin);
	free(ySpin);
	free(control);
	free(colorB);
	free(subWin);
	free(subSpin);
	free(capSpin);
	free(zSpin);
}

void static startCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->rowNum = j->rowSpin->value();
	j->colNum = j->colSpin->value();
	j->width = j->widthSpin->value();
	j->depth = j->depthSpin->value();
	j->xSpin->range(0,j->colSpin->value() * j->widthSpin->value());
	j->xSpin->value(0);
	j->xSpin->step(j->widthSpin->value());
	j->ySpin->step(j->depthSpin->value());
	j->ySpin->range(0, j->rowSpin->value() * j->depthSpin->value());
	j->ySpin->value(0);
	free(j->control->win->myField);
	heightField* h = new heightField(j->rowNum, j->colNum, j->width, j->depth, j->colorP->r(), j->colorP->g(), j->colorP->b(), j->capSpin->value());
	j->control->win->myField = h;
	j->topDown->myField = h;
	j->topDown->selectX = 0;
	j->topDown->selectY = 0;
	j->control->win->myField->selectX = (0);
	j->control->win->myField->selectY = (0);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->topDown->redraw();
}


void static smoothiBCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->xSpin->step(j->xSpin->step() / 2);
	j->ySpin->step(j->ySpin->step() / 2);
	j->control->win->myField->fractalize();
	j->subWin->hide();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->topDown->redraw();
}

void static capSpinCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->control->win->myField->capHeight = j->capSpin->value();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
}

void static xSpinCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->control->win->myField->selectX = j->xSpin->value();
	j->topDown->selectX = j->xSpin->value();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->topDown->redraw();
}

void static ySpinCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->control->win->myField->selectY = j->ySpin->value();
	j->topDown->selectY = j->ySpin->value();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->topDown->redraw();
}


void static transformBCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->control->win->myField->transform(j->zSpin->value());
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
}

void static topBCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->control->win->c->rot = identity3D();
	j->control->win->c->up = vec4(0, 1, 0, 1);
	j->control->win->c->eye = vec4(0, 0, 8, 1);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
}

void static frontBCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->control->win->c->rot = rotation3D(vec3(1, 0, 0), 90);
	j->control->win->c->up = vec4(0, 1, 0, 1);
	j->control->win->c->eye = vec4(0, 0, 7, 1);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
}


void static gridBCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->control->win->myField->griddy++;
	if (j->control->win->myField->griddy == 3){
		j->control->win->myField->griddy = 0;
	}
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
}

void static colorBCall(Fl_Widget* w, void* v){
	UI* j = ((UI*)v);
	j->control->win->myField->r = j->colorP->r();
	j->control->win->myField->g = j->colorP->g();
	j->control->win->myField->b = j->colorP->b();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	j->control->win->redraw();
}



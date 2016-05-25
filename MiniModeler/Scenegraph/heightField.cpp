#include "heightField.h"
#include <FL/Fl.H>
#include <FL/Gl.H>
#include <Fl/Fl_Gl_Window.H>
#define ABS_EPSILON .00000000000000001
#include <math.h>

heightField::heightField(int ro, int c, double wi, double de, double red, double green, double blue, int cappa){
	rows = ro;
	cols = c;
	width = wi;
	depth = de;
	r = red;
	g = green;
	b = blue;
	int one = rand() % 4;
	int two = rand() % 4;
	int three = rand() % 4;
	int four = rand() % 4;
	int temp = three;
	int temp2  = four;
	griddy = 1;
	capHeight = cappa;
	std::map<int, int> below4;
	std::map<int, int> below3;
	vertices = new std::list<mat4>;
	double w = (rows / 2) * depth;
	double d = (cols / 2) * width;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if (i == 0){
				vec3 vicky1((width * (j)) - d, (depth * (i)) - w, one);
				vec3 vicky2((width * (j + 1)) - d, (depth * (i)) - w, two);
				vec3 vicky3((width * (j + 1)) - d, (depth)* (i + 1) - w, three);
				vec3 vicky4((width * (j)) - d, (depth)* (i + 1) - w, four);
				mat4 matty(vicky1, vicky2, vicky3, vicky4);
				vertices->push_back(matty);
				below4[j] = four;
				below3[j] = three;
				one = two;
				four = three;
				three = rand() % 6 + 2;
				two = rand() % 6 + 2;
			}
			else{
				vec3 vicky1((width * (j)) - d, (depth * (i)) - w, below4[j]);
				vec3 vicky2((width * (j + 1)) - d, (depth * (i)) - w, below3[j]);
				vec3 vicky3((width * (j + 1)) - d, (depth)* (i + 1) - w, three);
				vec3 vicky4((width * (j)) - d, (depth)* (i + 1) - w, four);
				mat4 matty(vicky1, vicky2, vicky3, vicky4);
				vertices->push_back(matty);
				below4[j] = four;
				below3[j] = three;
				four = three;
				three = rand() % 6 + 2;
			}
		}
	}
}

void
heightField::draw(){
	double w = (rows / 2) * depth;
	double d = (cols / 2) * width;
	if (this->griddy == 1 || this->griddy == 2){
		for (std::list<mat4>::iterator it = this->vertices->begin(); it != this->vertices->end(); it++){
			glBegin(GL_LINE_LOOP);
			if ((*it)[0][0] == (selectX) - d && (*it)[0][1] == (selectY) - w){
				glColor3f(1.0, 1.0, 0.0);
			}
			else{
				glColor3f(1.0, 1.0, 1.0);
			}
			if (this->fracTimes == 0 || this->justFracked == 0){
				glVertex3f((*it)[0][0], (*it)[0][1], (*it)[0][2]);
			}
			else{
				(*it)[0][2] = searchHeight((*it)[0][0], (*it)[0][1], this->vertices);
				glVertex3f((*it)[0][0], (*it)[0][1], (*it)[0][2]);
			}
			if ((*it)[1][0] == (selectX) - d && (*it)[1][1] == (selectY) - w){
				glColor3f(1.0, 1.0, 0.0);
			}
			else{
				glColor3f(1.0, 1.0, 1.0);
			}
			if (this->fracTimes == 0 || this->justFracked == 0){
				glVertex3f((*it)[1][0], (*it)[1][1], (*it)[1][2]);
			}
			else{
				(*it)[1][2] = searchHeight((*it)[1][0], (*it)[1][1], this->vertices);
				glVertex3f((*it)[1][0], (*it)[1][1], (*it)[1][2]);
			}
			if ((*it)[2][0] == (selectX) - d && (*it)[2][1] == (selectY) - w){
				glColor3f(1.0, 1.0, 0.0);
			}
			else{
				glColor3f(1.0, 1.0, 1.0);
			}
			if (this->fracTimes == 0 || this->justFracked == 0){
				glVertex3f((*it)[2][0], (*it)[2][1], (*it)[2][2]);
			}
			else{
				(*it)[2][2] = searchHeight((*it)[2][0], (*it)[2][1], this->vertices);
				glVertex3f((*it)[2][0], (*it)[2][1], (*it)[2][2]);
			}
			if ((*it)[3][0] == (selectX) - d && (*it)[3][1] == (selectY) - w){
				glColor3f(1.0, 1.0, 0.0);
			}
			else{
				glColor3f(1.0, 1.0, 1.0);
			}
			if (this->fracTimes == 0 || this->justFracked == 0){
				glVertex3f((*it)[3][0], (*it)[3][1], (*it)[3][2]);
			}
			else{
				(*it)[3][2] = searchHeight((*it)[3][0], (*it)[3][1], this->vertices);
				glVertex3f((*it)[3][0], (*it)[3][1], (*it)[3][2]);
			}
			glEnd();
		}
	}
	if (this->griddy == 0 || this->griddy == 1){
		for (std::list<mat4>::iterator it = this->vertices->begin(); it != this->vertices->end(); it++){
			glBegin(GL_QUADS);
			if ((*it)[0][0] == (selectX) - d && (*it)[0][1] == (selectY) - w){
				glColor3f(1.0, 1.0, 0.0);
			}
			else if ((*it)[0][2] >= capHeight){
				glColor3f(1.0, 1.0, 1.0);
			}
			else{
				glColor3f(this->r, this->g, this->b);
			}
			if (this->fracTimes == 0 || this->justFracked == 0){
				glVertex3f((*it)[0][0], (*it)[0][1], (*it)[0][2]);
			}
			else{
				(*it)[0][2] = searchHeight((*it)[0][0], (*it)[0][1], this->vertices);
				glVertex3f((*it)[0][0], (*it)[0][1], (*it)[0][2]);
			}
			if ((*it)[1][0] == (selectX) - d && (*it)[1][1] == (selectY) - w){
				glColor3f(1.0, 1.0, 0.0);
			}
			else if ((*it)[1][2] >= capHeight){
				glColor3f(1.0, 1.0, 1.0);
			}
			else{
				glColor3f(this->r, this->g, this->b);
			}
			if (this->fracTimes == 0 || this->justFracked == 0){
				glVertex3f((*it)[1][0], (*it)[1][1], (*it)[1][2]);
			}
			else{
				(*it)[1][2] = searchHeight((*it)[1][0], (*it)[1][1], this->vertices);
				glVertex3f((*it)[1][0], (*it)[1][1], (*it)[1][2]);
			}
			if ((*it)[2][0] == (selectX) - d && (*it)[2][1] == (selectY) - w){
				glColor3f(1.0, 1.0, 0.0);
			}
			else if ((*it)[2][2] >= capHeight){
				glColor3f(1.0, 1.0, 1.0);
			}
			else{
				glColor3f(this->r, this->g, this->b);
			}
			if (this->fracTimes == 0 || this->justFracked == 0){
				glVertex3f((*it)[2][0], (*it)[2][1], (*it)[2][2]);
			}
			else{
				(*it)[2][2] = searchHeight((*it)[2][0], (*it)[2][1], this->vertices);
				glVertex3f((*it)[2][0], (*it)[2][1], (*it)[2][2]);
			}
			if ((*it)[3][0] == (selectX) - d && (*it)[3][1] == (selectY) - w){
				glColor3f(1.0, 1.0, 0.0);
			}
			else if ((*it)[3][2] >= capHeight){
				glColor3f(1.0, 1.0, 1.0);
			}
			else{
				glColor3f(this->r, this->g, this->b);
			}
			if (this->fracTimes == 0 || this->justFracked == 0){
				glVertex3f((*it)[3][0], (*it)[3][1], (*it)[3][2]);
			}
			else{
				(*it)[3][2] = searchHeight((*it)[3][0], (*it)[3][1], this->vertices);
				glVertex3f((*it)[3][0], (*it)[3][1], (*it)[3][2]);
			}
			glEnd();
		}
	}
	this->justFracked = 0;
}

void
heightField::transform(double newHeight){
	double w = (rows / 2) * depth;
	double d = (cols / 2) * width;
	for (std::list<mat4>::iterator it = this->vertices->begin(); it != this->vertices->end(); it++){
		if ((*it)[0][0] == (selectX) - d && (*it)[0][1] == (selectY) - w){
			(*it)[0][2] = (*it)[0][2] + newHeight;
		}
		if ((*it)[1][0] == (selectX) - d && (*it)[1][1] == (selectY) - w){
			(*it)[1][2] = (*it)[1][2] + newHeight;
		}
		if ((*it)[2][0] == (selectX) - d && (*it)[2][1] == (selectY) - w){
			(*it)[2][2] = (*it)[2][2] + newHeight;
		}
		if ((*it)[3][0] == (selectX) - d && (*it)[3][1] == (selectY) - w){
			(*it)[3][2] = (*it)[3][2] + newHeight;
		}
	}
}

double
heightField::random(){
	double one = (rand() % 50) / 10;
	one = one / (fracTimes * 2);
	int two = rand();
	if (remainder(two, 2) == 0){
		one = one * (-1);
	}
	return one;
}

double
heightField::searchHeight(double x, double y, std::list<mat4>* theres){
	std::pair<double, double> check(x, y);
	for (std::list<mat4>::iterator it = theres->begin(); it != theres->end(); it++){
		if (fabs((*it)[0][0] - x) < ABS_EPSILON && fabs((*it)[0][1] - y) < ABS_EPSILON){
			return (*it)[0][2];
		}
		else if (fabs((*it)[1][0] - x) < ABS_EPSILON && fabs((*it)[1][1] - y) < ABS_EPSILON){
			return (*it)[1][2];
		}
		else if (fabs((*it)[2][0] - x) < ABS_EPSILON && fabs((*it)[2][1] - y) < ABS_EPSILON){
			return (*it)[2][2];
		}
		else if (fabs((*it)[3][0] - x) < ABS_EPSILON && fabs((*it)[3][1] - y) < ABS_EPSILON){
			return (*it)[3][2];
		}
	}
	return NULL;
}

void
heightField::fractalize(){
	justFracked = 1;
		double w = (rows / 2) * depth;
		double d = (cols / 2) * width;
		std::list<mat4>* newVerts;
		fracTimes++;
		half = half / 2;
		newVerts = new std::list<mat4>;
		double h;
		std::list<vec3> sames;	
		for (std::list<mat4>::iterator it = this->vertices->begin(); it != this->vertices->end(); it++){
			vec4 vicky1((*it)[0][0], (*it)[0][1], (*it)[0][2], 0);
			vec4 vicky2(((*it)[1][0]) - (half * width), (*it)[1][1], random() + (((*it)[1][2] + (*it)[0][2])/2), 0); 
			vec4 vicky3((*it)[2][0] - (half * width), (*it)[2][1] - (half * depth), random() + (((*it)[2][2] + (*it)[1][2] + (*it)[0][2] + (*it)[3][2])/4), 0);
			vec4 vicky4((*it)[3][0], (*it)[3][1] - (half * depth), random() + (((*it)[3][2] + (*it)[0][2])/2), 0);
			mat4 matty(vicky1, vicky2, vicky3, vicky4);
			newVerts->push_back(matty);

			vec4 vicky5 = vicky2;
			vec4 vicky6(((*it)[1][0]), (*it)[1][1], (*it)[1][2], 0);
			vec4 vicky7((*it)[2][0], (*it)[2][1] - (half * depth), random() + (((*it)[2][2] + (*it)[1][2])/2), 0);
			vec4 vicky8 = vicky3;
			mat4 matty2(vicky5, vicky6, vicky7, vicky8);
			newVerts->push_back(matty2);

			vec4 vicky9 = vicky3;
			vec4 vicky10 = vicky7;
			vec4 vicky11((*it)[2][0], (*it)[2][1], (*it)[2][2], 0);
			vec4 vicky12((*it)[2][0] - (half * width), (*it)[2][1], random() + (((*it)[2][2] + (*it)[3][2])/2), 0);
			mat4 matty3(vicky9, vicky10, vicky11, vicky12);
			newVerts->push_back(matty3);

			vec4 vicky13 = vicky4;
			vec4 vicky14 = vicky3;
			vec4 vicky15 = vicky12;
			vec4 vicky16((*it)[3][0], (*it)[3][1], (*it)[3][2], 0);
			mat4 matty4(vicky13, vicky14, vicky15, vicky16);
			newVerts->push_front(matty4);
		}
		free(this->vertices);
		this->vertices = newVerts;
}
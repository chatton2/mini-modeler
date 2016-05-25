#include "algebra3.h"
#include <list>
#include <map>
#include <random>

class heightField{
private:
	// the OpenGL window
public:
	int rows;
	int cols;
	double width;
	double depth;
	double r;
	double g;
	double b;
	double selectX;
	double selectY;
	int griddy;
	int justFracked = 0;
	double capHeight;
	int fracTimes = 0;
	double half = 1.0;
	std::list<mat4>* vertices;
	heightField(int ro, int c, double wi, double de, double red, double green, double blue, int cappa);				// constructor
	~heightField(){ vertices->clear(); free(vertices);};
	void draw(); 
	void fractalize();
	double random();
	double searchHeight(double x, double y, std::list<mat4>* theres);
	void transform(double newHeight);
};




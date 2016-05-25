#include <FL/Fl.H>
#include <FL/Gl.H>
#include <Fl/Fl_Gl_Window.H>
#include <GL/glut.h> // Include the GLUT header file  
#include "algebra3.h"
//#include "cubeWin.h"

class Camera{

private:
	
public:
	mat4 rot;			// Current rotation matrix 
	vec4 up;				// Current up vector
	vec4 eye;			// Current eye/camera position
	Camera(float r, float phi, float theta);
	~Camera(){};
	void increasePhi(float inc);		// increase the phi angle. Note a negative value will decrease it. 
	void increaseTheta(float inc);		// increase the theta angle
	void increaseRad(float inc);		// increase the radius
	const vec3 getEye();		// get the current eye position
	const vec3 getUp();		// get the current up vector



};
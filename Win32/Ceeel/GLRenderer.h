#pragma once
#include "stdafx.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>


#include <glm/vec3.hpp>
using namespace glm;

#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "VisualObject.h"

#define _FL(iVal) iVal.0/255.0

#define BACK_COLOR _FL(196), _FL(212), _FL(224)
#define TOKEN_COLOR _FL(223), _FL(110), _FL(33)
#define GRID_COLOR _FL(25), _FL(52), _FL(70)
#define POINT_COLOR _FL(72), _FL(18), _FL(14)




class Camera {
public:
	float x, y, z;
	Camera() :x(0.0), y(0.0), z(0.0) {}
};
class ViewingVolume {
protected:
	float z_near, z_far;
	float y_bottom, y_top;
	float x_left, x_right;
public:
	void set_near_far(float observer_z, float n, float f) {
		z_near = 1.0;// = observer_z - n;
		z_far = 10.0; // i = observer_z - f;
	}
	void set_left_right(float left, float right) {
		x_left = left;
		x_right = right;
	}
	void set_bottom_top(float bottom, float top){
		y_bottom = bottom;
		y_top = top;
		}
	/*float z_a() const {
		return z_begin;
	}
	float z_b() const {
		return z_end;
	}*/
	void frustrum() {
		glFrustum(x_left, x_right, y_bottom, y_top, z_near, z_far);
	}
	void ortho() {
		glOrtho(x_left, x_right, y_bottom, y_top, z_near, z_far);
	}
	
};
class Board {
private:
	float m_xrot, m_yrot;
	Mesh model;
public:
	Board(const string&);
	void draw();
};

class CGLRenderer
{
	//Camera Variables
	Camera observer;
	ViewingVolume perspective_volume;
	ViewingVolume ortho_volume;
	float m_xpos, m_ypos, m_zoom;
	//Board Rotation Variables
	Board m_board;
public:

	CGLRenderer(void);
	virtual ~CGLRenderer(void);
	bool CreateGLContext(CDC* pDC); 	// Creates OpenGL Rendering Context
	void PrepareScene();		// Scene preparation stuff
	void Reshape(int w, int h);	// Changing viewport
	void DrawScene(CDC* pDC, PointCloud *);		// Draws the scene

	void DestroyScene();		// Cleanup

protected:
	void SetData();	                        // Creates VAO and VBOs and fill them with data

protected:
	void FinishDrawing();

	HGLRC	 m_hrc;                        // OpenGL Rendering Context 
	
	GLuint m_vaoID[2];			// two vertex array objects, one for each drawn object
	GLuint m_vboID[3];			// three VBOs
};
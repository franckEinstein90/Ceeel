#pragma once
#include "stdafx.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#define _FL(iVal) iVal.0/255.0

#define BACK_COLOR _FL(196), _FL(212), _FL(224)
#define TOKEN_COLOR _FL(223), _FL(110), _FL(33)
/*
#c4d4e0(196, 212, 224)
#193446	(25, 52, 70)
#df6e21(223, 110, 33)
#48120e(72, 18, 14)
*/
class Camera {
	float m_xpos, m_ypos, m_zoom;
public:
};

class Board {
private:
	float m_xrot, m_yrot;
public:
	void draw();
};
class CGLRenderer
{
	//Camera Variables
	float m_xpos, m_ypos, m_zoom;
	//Board Rotation Variables
	Board m_board;
public:

	CGLRenderer(void);
	virtual ~CGLRenderer(void);
	bool CreateGLContext(CDC* pDC); 	// Creates OpenGL Rendering Context
	void PrepareScene();		// Scene preparation stuff
	void Reshape(int w, int h);	// Changing viewport
	void DrawScene(CDC* pDC);		// Draws the scene

	void DestroyScene();		// Cleanup

protected:
	void SetData();	                        // Creates VAO and VBOs and fill them with data

protected:
	void FinishDrawing();

	HGLRC	 m_hrc;                        // OpenGL Rendering Context 
	
	GLuint m_vaoID[2];			// two vertex array objects, one for each drawn object
	GLuint m_vboID[3];			// three VBOs
};
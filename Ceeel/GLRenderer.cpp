#include "stdafx.h"
#include "GLRenderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <glm/vec3.hpp>

#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

Board::Board(const string& file_name) {
	string model;
	string info_package;
	std::vector< glm::vec3 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;
	ifstream infile;
	infile.open(file_name);
	if (!infile) {
		AfxMessageBox(_T("unable to oo"));
	}
	while (getline(infile, info_package)) {
		if (info_package.substr(0, 2) == "v ")
		{
			istringstream s(info_package.substr(2));
			glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
			vertices.push_back(v);
		}
		else if (info_package.substr(0, 2) == "f ")
		{
			istringstream s(info_package.substr(2));
			string a, b, c;
			s >> a; s >> b; s >> c;

		//	a--; b--; c--;
		elements.push_back(a); elements.push_back(b); elements.push_back(c);
		}
		else if (info_package[0] == '#')
		{
			/* ignoring this line */
		}
		else
		{
			/* ignoring this line */
		}
	}
}


CGLRenderer::CGLRenderer():m_board("C:\\Ceel_the_game\\Ceeel\\assets\\board.obj")
{
}


CGLRenderer::~CGLRenderer()
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	HGLRC tempContext = wglCreateContext(pDC->m_hDC);
	wglMakeCurrent(pDC->m_hDC, tempContext);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		AfxMessageBox(_T("GLEW is not initialized!"));
	}

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, 0,
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		m_hrc = wglCreateContextAttribsARB(pDC->m_hDC, 0, attribs);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);
		wglMakeCurrent(pDC->m_hDC, m_hrc);
	}
	else
	{	//It's not possible to make a GL 3.x context. Use the old style context (GL 2.1 and before)
		m_hrc = tempContext;
	}

	//Checking GL version
	const GLubyte *GLVersionString = glGetString(GL_VERSION);

	//Or better yet, use the GL3 way to get the version number
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

	if (!m_hrc) return false;

	return true;
}

void CGLRenderer::PrepareScene()
{
//	glClearColor(248.0/255.0, 243.0/255.0, 230.0/255.0, 0.0);
	glClearColor(BACK_COLOR, 0.0);	
	SetData();
}

void CGLRenderer::SetData()
{
	// First simple object
	float* vert = new float[9];	// vertex array
	float* col = new float[9];	// color array

	vert[0] = -0.3f; vert[1] = 0.5f; vert[2] = -1.0f;
	vert[3] = -0.8f; vert[4] = -0.5f; vert[5] = -1.0f;
	vert[6] = 0.2f; vert[7] = -0.5f; vert[8] = -1.0f;

	col[0] = 1.0f; col[1] = 0.0f; col[2] = 0.0f;
	col[3] = 0.0f; col[4] = 1.0f; col[5] = 0.0f;
	col[6] = 0.0f; col[7] = 0.0f; col[8] = 1.0f;

	// Second simple object
	float* vert2 = new float[9];	// vertex array

	vert2[0] = -0.2f; vert2[1] = 0.5f; vert2[2] = -1.0f;
	vert2[3] = 0.3f; vert2[4] = -0.5f; vert2[5] = -1.0f;
	vert2[6] = 0.8f; vert2[7] = 0.5f; vert2[8] = -1.0f;

	// Two VAOs allocation
	glGenVertexArrays(2, &m_vaoID[0]);

	// First VAO setup
	glBindVertexArray(m_vaoID[0]);

	glGenBuffers(2, m_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vert, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), col, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Second VAO setup	
	glBindVertexArray(m_vaoID[1]);

	glGenBuffers(1, &m_vboID[2]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[2]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vert2, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	delete[] vert;
	delete[] vert2;
	delete[] col;

//	gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void CGLRenderer::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Board::draw() {
	float mid_z = -1;

	float left_x = -2.0;
	float right_x = 2.0;
	float front_z = 2.0;
	float back_z = -2.0;
	float top_y = 2.0;
	float bottom_y = -2.0;

	glColor3f(TOKEN_COLOR);
	glBegin(GL_QUADS);
	glVertex3f(left_x, top_y, front_z);
	glVertex3f(0.0, top_y, front_z);
	glVertex3f(0.0, 0.0, front_z);
	glVertex3f(left_x, 0.0, front_z);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(right_x, -0.5, back_z);
	glVertex3f(0.0, -0.5, back_z);
	glVertex3f(0.0, 0.0, back_z);
	glVertex3f(right_x, 0.0, back_z);
	glEnd();
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho (-5,5,-5,5,-5,5);

	float near_val = 1.0;
	float far_val = 10.0;

	float frustrum_left = -2.0;
	float frustrum_right = -1 * frustrum_left;
	glFrustum(frustrum_left, frustrum_right, -1.0, 1.0, near_val, far_val);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float my_location = 5.0;
	gluLookAt(0.0, 0.0, my_location, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	m_board.draw();
	
	SwapBuffers(pDC->m_hDC);
}
void CGLRenderer::FinishDrawing()
{
	glFinish();
	glFlush();
}

void CGLRenderer::DestroyScene()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(3, m_vboID);

	glBindVertexArray(0);
	glDeleteVertexArrays(2, m_vaoID);



	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}
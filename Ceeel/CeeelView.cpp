
// CeeelView.cpp : implementation of the CCeeelView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Ceeel.h"
#endif

#include "CeeelDoc.h"
#include "CeeelView.h"

    // 


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCeeelView

IMPLEMENT_DYNCREATE(CCeeelView, CView)

BEGIN_MESSAGE_MAP(CCeeelView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

const char* const CCeeelView::_ErrorStrings[] = {
	{ "No Error" },                     // 0
	{ "Unable to get a DC" },           // 1
	{ "ChoosePixelFormat failed" },     // 2
	{ "SelectPixelFormat failed" },     // 3
	{ "wglCreateContext failed" },      // 4
	{ "wglMakeCurrent failed" },        // 5
	{ "wglDeleteContext failed" },      // 6
	{ "SwapBuffers failed" },           // 7
};


// CCeeelView construction/destruction

CCeeelView::CCeeelView():m_hRC(0), m_pDC(0), m_ErrorString(_ErrorStrings[0]) 
{
	// TODO: add construction code here

}

CCeeelView::~CCeeelView()
{
}

BOOL CCeeelView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// CCeeelView drawing

void CCeeelView::OnDraw(CDC* /*pDC*/)
{
	CCeeelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

//	m_glRenderer.set_camera(camera_vector);
	m_glRenderer.DrawScene(m_pDC);
}


// CCeeelView printing

BOOL CCeeelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCeeelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCeeelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCeeelView diagnostics

#ifdef _DEBUG
void CCeeelView::AssertValid() const
{
	CView::AssertValid();
}

void CCeeelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCeeelDoc* CCeeelView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCeeelDoc)));
	return (CCeeelDoc*)m_pDocument;
}
#endif //_DEBUG


// CCeeelView message handlers


int CCeeelView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pDC = new CClientDC(this);
	m_glRenderer.CreateGLContext(m_pDC);
	m_glRenderer.PrepareScene();
	return 0;
}


void CCeeelView::OnDestroy()
{
	CView::OnDestroy();

	if (FALSE == ::wglDeleteContext(m_hRC))
	{
		SetError(6);
	}

	if (m_pDC)
	{
		delete m_pDC;
	}

}


void CCeeelView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_glRenderer.Reshape(cx, cy);
}

/////////////////////////////////////////////////////////////////////////////
// GL Rendering Context Creation Functions
//
// Since we are using Windows native windowing, we need to set up our own
// OpenGL rendering context. These functions do it to the main view area.
// It is possible to do it to a smaller sub view. If you are curious, you can
// find tutorials on how to do that on the net.
//

// Error reporting utility
void CCeeelView::SetError(int e)
{
	// if there was no previous error,
	// then save this one
	if (_ErrorStrings[0] == m_ErrorString)
	{
		m_ErrorString = _ErrorStrings[e];
	}
}


void CCeeelView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_CONTROL)
	{
		if (nFlags & MK_LBUTTON)
		{
			// Left mouse button is being
			// pressed. Rotate the camera.
			if (m_lastMouseX != -1)
			{
//				m_yrot += point.y - m_lastMouseY;
//				m_xrot += point.x - m_lastMouseX;
				// Redraw the viewport.
				OnDraw(NULL);
			}
//			m_lastMouseX = point.x;
//			m_lastMouseY = point.y;
		}

		// etc...

		else
		{
//			m_lastMouseX = -1;
//			m_lastMouseY = -1;
		}
	}
	else
	{
//		m_lastMouseX = -1;
//		m_lastMouseY = -1;
	}// TODO: Add your message handler code here and/or call default

	CView::OnMouseMove(nFlags, point);
}

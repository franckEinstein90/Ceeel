
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Ceeel.h"
#include "CeeelDoc.h"
#include "CeeelView.h"
#include "InfoPanel.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)	

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame():splitter(this)
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	bool init_static = splitter.init_static();
	if (!init_static)
	{
		MessageBox(_T("Error setting up splitter frames!"), _T("Init Error!"),
			MB_OK | MB_ICONERROR);
		return FALSE;
	}
	CRect cr;  // client rectangle -
	GetClientRect(&cr);
	CSize col1_size(cr.Width() / 4, cr.Height());
	CSize col2_size(cr.Width() - col1_size.cx, cr.Height());
	bool init_view1 = splitter.init_view(0, col1_size, RUNTIME_CLASS(InfoPanel), pContext);
	if (!init_view1)
	{
		MessageBox(_T("Error setting up splitter frames!"), _T("Init Error!"),
			MB_OK | MB_ICONERROR);
		return FALSE;
	}
	bool init_view2 = splitter.init_view(1, col2_size, RUNTIME_CLASS(CCeeelView), pContext);
	if(!init_view2)
	{
		MessageBox(_T("Error setting up splitter frames!"),
			_T("Init Error!"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
//..	if (nType != SIZE_MINIMIZED)
//	{
/*		m_main_splitter.SetRowInfo(0, cy, 0);
		m_main_splitter.SetColumnInfo(0, cx - INFOBAR_SIZE, 0);
		m_main_splitter.SetColumnInfo(1, INFOBAR_SIZE, 0);

		// etc...

		m_main_splitter.RecalcLayout();
		m_viewport_splitter.RecalcLayout();
	}
	// TODO: Add your message handler code here*/
}


afx_msg LRESULT CMainFrame::OnOrthomode(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

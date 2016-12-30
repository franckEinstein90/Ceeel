// Dash.cpp : implementation file
//

#include "stdafx.h"
#include "Ceeel.h"
#include "Dash.h"
#include "CeeelDoc.h"

// CDash

IMPLEMENT_DYNCREATE(CDash, CView)

CDash::CDash()
{

}

CDash::~CDash()
{
}

BEGIN_MESSAGE_MAP(CDash, CView)
END_MESSAGE_MAP()


// CDash drawing

void CDash::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CDash diagnostics

#ifdef _DEBUG
void CDash::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDash::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDash message handlers

// InfoPanel.cpp : implementation file
//

#include "stdafx.h"
#include "Ceeel.h"
#include "InfoPanel.h"


// InfoPanel

IMPLEMENT_DYNCREATE(InfoPanel, CFormView)

InfoPanel::InfoPanel()
	: CFormView(IDD_FORMVIEW)
{

}

InfoPanel::~InfoPanel()
{
}

void InfoPanel::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(InfoPanel, CFormView)
END_MESSAGE_MAP()


// InfoPanel diagnostics

#ifdef _DEBUG
void InfoPanel::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void InfoPanel::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// InfoPanel message handlers

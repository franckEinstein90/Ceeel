// InfoPanel.cpp : implementation file
//

#include "stdafx.h"
#include "Ceeel.h"
#include "InfoPanel.h"
#include "CeeelDoc.h"

#include <string>
using namespace std;

#include "VisualObject.h"
// InfoPanel

IMPLEMENT_DYNCREATE(InfoPanel, CFormView)

InfoPanel::InfoPanel()
	: CFormView(IDD_FORMVIEW), m_data_dimension(2)
{

}

InfoPanel::~InfoPanel()
{
}

void InfoPanel::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_data_input_box);
}

BEGIN_MESSAGE_MAP(InfoPanel, CFormView)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &InfoPanel::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &InfoPanel::OnNMReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_BUTTON2, &InfoPanel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_VIEW_FRONT_BUTTON, &InfoPanel::OnBnClickedViewFrontButton)
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


void InfoPanel::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void InfoPanel::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void InfoPanel::OnBnClickedButton2()
{

	UpdateData();// Read data UpdateData();
	CEdit* editTitle = (CEdit*)GetDlgItem(IDC_EDIT1);
	CString temp;
	editTitle->GetWindowText(temp);
	CCeeelDoc* pDoc = (CCeeelDoc*) GetDocument();
	pDoc->update_data(temp, this->m_data_dimension);

	
	UpdateData(FALSE); // WriteData
										 // TODO: Add your control notification handler code here
	pDoc->UpdateAllViews(this);
}


void InfoPanel::OnBnClickedViewFrontButton()
{
	// TODO: Add your control notification handler code here
}

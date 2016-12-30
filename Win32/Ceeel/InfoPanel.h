#pragma once



// InfoPanel form view

class InfoPanel : public CFormView
{
	DECLARE_DYNCREATE(InfoPanel)

protected:
	InfoPanel();           // protected constructor used by dynamic creation
	virtual ~InfoPanel();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};




// CeeelView.h : interface of the CCeeelView class
//

#pragma once


class CCeeelView : public CView
{
protected: // create from serialization only
	CCeeelView();
	DECLARE_DYNCREATE(CCeeelView)

// Attributes
public:
	CCeeelDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);



private:


	CGLRenderer m_glRenderer;
	//Rendering Context and Device Context Pointers
	HGLRC     m_hRC;
	CDC*      m_pDC;

	//Error Handling
	void SetError(int e);
	static const char* const _ErrorStrings[];
	const char* m_ErrorString;

// Implementation
public:
	virtual ~CCeeelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in CeeelView.cpp
inline CCeeelDoc* CCeeelView::GetDocument() const
   { return reinterpret_cast<CCeeelDoc*>(m_pDocument); }
#endif


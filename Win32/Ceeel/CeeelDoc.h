
// CeeelDoc.h : interface of the CCeeelDoc class
//


#pragma once

#include "DataSet.h"
#include "VisualObject.h"
class CCeeelDoc : public CDocument
{
protected: // create from serialization only
	CCeeelDoc();
	DECLARE_DYNCREATE(CCeeelDoc)

/************DATA UPDATING*******************/
protected:
	DataSet m_data_set;
public:
	void update_data(const CString&, size_t);

/*************POINT_CLOUD*******************/
public:
	PointCloud * m_point_cloud;

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CCeeelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

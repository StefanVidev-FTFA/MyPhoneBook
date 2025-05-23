
// CitiesDoc.h : interface of the CCitiesDoc class
//


#pragma once
#include "CitiesData.h"


class CCitiesDoc : public CDocument
{
protected: // create from serialization only
	CCitiesDoc() noexcept;
	DECLARE_DYNCREATE(CCitiesDoc)

// Attributes
public:
	CCitiesArray m_oInitialCitiesArray;
	CCitiesData* m_oCitiesData;
	int m_SelectByIdTarget = -1;

// Operations
public:

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
	virtual ~CCitiesDoc();
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

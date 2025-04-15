
// CitiesView.h : interface of the CCitiesView class
//

#pragma once
#include "CitiesArray.h"
#include "CitiesDoc.h"

using namespace std;

class CCitiesView : public CListView
{
protected: // create from serialization only
	CCitiesView() noexcept;
	DECLARE_DYNCREATE(CCitiesView)
	void SetViewStyle();
	void DeclareCityColums(int nAlignment);
	void InsertCityRows(CCitiesArray& oCitiesArray);
	void InsertACityRow(CITIES& recCity);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);


	int m_SelectedIndex=-1;
	int m_nIdToBeSelected = -1;
	CITIES m_recCityForUpdate;
	CMap<int,int,int,int> entriesMap;


	void OnInsert();
	void OnDelete();
	void SelectById();
	void SelectAll();
	void UpdateByID();

	CListCtrl* m_pListCtrl;
// Attributes
public:
	CCitiesDoc* GetDocument() const;

	enum CityColumn
	{
		COLUMN_ID=0,
		COLUMN_CITY_NAME,
		COLUMN_CITY_REGION,
	};
	enum UpdateMode
	{
		LOAD_INIT = 0,
		INSERT_OR_DELETE,
		SELECT_BY_ID,
		SELECT_ALL,
		UPDATE_BY_ID
	};


// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CCitiesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDoc*>(m_pDocument); }
#endif


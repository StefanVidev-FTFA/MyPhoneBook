#pragma once
#include "CitiesArray.h"
#include "CitiesDoc.h"

using namespace std;

// CitiesView.h : interface of the CCitiesView class
//
class CCitiesView : public CListView
{
protected:
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
public:
	CCitiesDoc* GetDocument() const;

	enum CityColumn
	{
		CityColumnId=0,
		CityColumnName,
		CityColumnRegion,
	};
	enum SqlOperation
	{
		SqlOperationLoadInit = 0,
		SqlOperationInsertOrDelete,
		SqlOperationSelectById,
		SqlOperationSelectAll,
		SqlOperationUpdateById
	};


// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();


public:
	virtual ~CCitiesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};
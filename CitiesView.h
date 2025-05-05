#pragma once
#include "CitiesDoc.h"
#include "CommonListView.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCitiesView
///<summary> ���� ������ �� ������������� �� ������������ �� ����/��� �� ������ ����� ///</summary>
class CCitiesView : public CCommonListView
{
// Constants
// ----------------
public:
	enum CityColumn
	{
		CityColumnId = 0,
		CityColumnName,
		CityColumnRegion,
	};

// Defines
// ----------------
 	DECLARE_DYNCREATE(CCitiesView)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
protected:
	CCitiesView() noexcept;

// Methods
// ----------------
protected:
	///<summary> ������� �� ����� �� ������ � ���� ��������///</summary>
	void InsertRows(CSmartArray<CITIES>& oTableTypeArray);
	///<summary> ������� �� ��� ����� � ���� ��������///</summary>
	void InsertACityRow(CITIES& recCity);
	///<summary> ������� �� ��� ���� ��� ������ ����� ���� ������ � ����������� ///</summary>
	void RequestInsert();
	///<summary> ������� ���� ��� ������ ����� ���� ������ � ����������� ///</summary>
	void RequestDelete();
	///<summary> ������ ���� �� ������ ����� ���� ������ � ����������� � ����������� ���� ���� ///</summary>
	void RequestSelectById();
	///<summary> ������ � ����������� ������ ������ �� ������ ����� � ������� ///</summary>
	void RequestSelectAll();
	///<summary> �������� ������������ �� ���� ����� � ������� ���� ����������������� ����� ///</summary>
	void RequestUpdate();

// Overrides
// ----------------
public:
	CCitiesDoc* GetDocument() const;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CCitiesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnInitialUpdate();
	void CreateListOnInit() override;
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	// Members
	// ----------------
	CListCtrl* m_pListCtrl;
	int m_SelectedIndex = -1;
	int m_nIdToBeSelected = -1;
	CMap<int, int, int, int> entriesMap;
};
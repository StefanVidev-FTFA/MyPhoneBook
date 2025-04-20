#pragma once
#include "CitiesArray.h"
#include "CitiesDoc.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

///<summary> ���� ������ �� ������������� �� ������������ �� ����/��� �� ������ ����� ///</summary>
class CCitiesView : public CListView
{

	// Constructor / Destructor
	// ----------------
protected:
	CCitiesView() noexcept;
	DECLARE_DYNCREATE(CCitiesView)
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);



	void SetViewStyle();
	void DeclareCityColums(int nAlignment);
	void InsertCityRows(CCitiesArray& oCitiesArray);
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
		SqlOperationInsert,
		SqlOperationSelectById,
		SqlOperationSelectAll,
		SqlOperationUpdateById,
		SqlOperationDelete
	};


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
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	// Members
	// ----------------
	CListCtrl* m_pListCtrl;
	int m_SelectedIndex = -1;
	int m_nIdToBeSelected = -1;
	CMap<int, int, int, int> entriesMap;
};
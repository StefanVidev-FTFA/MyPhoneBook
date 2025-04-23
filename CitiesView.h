#pragma once
#include "CitiesArray.h"
#include "CitiesDoc.h"
#include "CommonListView.h"


using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

///<summary> ���� ������ �� ������������� �� ������������ �� ����/��� �� ������ ����� ///</summary>
class CCitiesView : public CCommonListView
{

	// Constructor / Destructor
	// ----------------
protected:
	CCitiesView() noexcept;
	DECLARE_DYNCREATE(CCitiesView)
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

	template <typename tableType>
	void InsertCityRows(CSmartArray<tableType>& oTableTypeArray)
	{
		for (INT_PTR i = 0; i < oTableTypeArray.GetCount(); ++i)
		{
			tableType* pRecItem = static_cast<tableType*>(oTableTypeArray.GetAt(i));

			if (pRecItem != nullptr) {

				CString sId;
				sId.Format(_T("%d"), pRecItem->nId);

				int row = m_pListCtrl->InsertItem(i, sId);
				m_pListCtrl->SetItemText(i, 1, CString(pRecItem->szCityName));
				m_pListCtrl->SetItemText(row, 2, CString(pRecItem->szRegion));

			}
		}
	}

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

	void CreateListOnInit() override;


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
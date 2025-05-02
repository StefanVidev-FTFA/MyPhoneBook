#pragma once
#include "CitiesDoc.h"
#include "CommonListView.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCitiesView
///<summary> Клас служещ за представянето на информацията за град/ове от базата данни ///</summary>
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
	///<summary> Въвежда на набор от записи в лист контрола///</summary>
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


				entriesMap.SetAt(pRecItem->nId, i);

			}
		}
	}
	///<summary> Въвежда на нов запис в лист контрола///</summary>
	void InsertACityRow(CITIES& recCity);
	///<summary> Въвежда на нов град във базата данни чрез диалог с потребителя ///</summary>
	void RequestInsert();
	///<summary> Изтрива град във базата данни чрез диалог с потребителя ///</summary>
	void RequestDelete();
	///<summary> Избира град от базата данни чрез диалог с потребителя и визуализира само него ///</summary>
	void RequestSelectById();
	///<summary> Избира и визуализира всички записи от базата данни в изгледа ///</summary>
	void RequestSelectAll();
	///<summary> Обновява информацията за град който е посочен чрез идентификационнен номер ///</summary>
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
	afx_msg void OnFilePrintPreview();
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
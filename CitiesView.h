#pragma once
#include "CitiesArray.h"
#include "CitiesDoc.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

///<summary> Клас служещ за представянето на информацията за град/ове от базата данни ///</summary>
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
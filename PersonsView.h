#pragma once
#include "PersonsDoc.h"
#include "CommonListView.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsView
class CPersonsView : public CCommonListView
{
// Defines
// ----------------
	DECLARE_DYNCREATE(CPersonsView)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
protected:
	CPersonsView() noexcept;

// Methods
// ----------------
protected:
	///<summary> Въвежда на нов град във базата данни чрез диалог с потребителя </summary>
	void RequestInsert();
	///<summary> Изтрива град във базата данни чрез диалог с потребителя </summary>
	void RequestDelete();
	///<summary> Избира град от базата данни чрез диалог с потребителя и визуализира само него </summary>
	void RequestSelectById();
	///<summary> Избира и визуализира всички записи от базата данни в изгледа </summary>
	void RequestSelectAll();
	///<summary> Обновява информацията за град който е посочен чрез идентификационнен номер </summary>
	void RequestUpdate();
	///<summary> Въвежда записи за потребител </summary>
	void InsertRows(CSmartArray<PERSONS>& oPersonsSmartArray);

// Overrides
// ----------------
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void CreateListOnInit() override;
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

public:
	CPersonsDoc* GetDocument() const;
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CPersonsView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Members
// ----------------
protected:
	CListCtrl* m_pListCtrl;
	int m_SelectedIndex = -1;

	typedef CMap<int, int, CString, const CString&> aCitiesMap;
};

#pragma once

#include "PhoneTypesDoc.h"
#include "CommonListView.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesView
class CPhoneTypesView : public CCommonListView
{
// Defines
// ----------------
	DECLARE_DYNCREATE(CPhoneTypesView)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
protected:
	CPhoneTypesView() noexcept;

// Methods
// ----------------
protected:
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
	///<summary> Въвежда записи от конкретен тип </summary>
	void InsertRows(CSmartArray<PHONE_TYPES>& oPhoneTypesArray);

// Overrides
// ----------------
public:
	CPhoneTypesDoc* GetDocument() const;
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CPhoneTypesView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void CreateListOnInit() override;
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

// Members
// ----------------
	CListCtrl* m_pListCtrl;
	int m_SelectedIndex = -1;
};

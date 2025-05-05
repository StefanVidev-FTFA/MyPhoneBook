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
	///<summary> ������� ������ �� ��������� ��� </summary>
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

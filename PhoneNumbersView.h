#pragma once

#include "PhoneNumbersDoc.h"
#include "CommonListView.h"

class CPhoneNumbersView : public CCommonListView
{
// Defines
// ----------------
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CPhoneNumbersView)

// Constructor / Destructor
// ----------------
protected:
    CPhoneNumbersView() noexcept;

// Methods
// ----------------
public:
	CPhoneNumbersDoc* GetDocument() const;
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
	///<summary> ������� ���� ��� ����� </summary>
	void InsertASingleRow(PHONE_NUMBERS& recItem);
	///<summary> ������� ������ �� ��������� ��� </summary>
	void InsertRows(CSmartArray<PHONE_NUMBERS>& oTableTypeArray,
		CMap<int, int, CString, const CString&>& personsMap,
		CMap<int, int, CString, const CString&>& phoneTypesMap
	);

	// Overrides
public:
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CPhoneNumbersView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	void CreateListOnInit() override;
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

// Members
// ----------------
	int m_SelectedIndex = -1;
	CListCtrl* m_pListCtrl;
};


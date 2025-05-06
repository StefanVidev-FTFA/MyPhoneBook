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
	///<summary> ������� �� ��� ���� ��� ������ ����� ���� ������ � ����������� </summary>
	void RequestInsert();
	///<summary> ������� ���� ��� ������ ����� ���� ������ � ����������� </summary>
	void RequestDelete();
	///<summary> ������ ���� �� ������ ����� ���� ������ � ����������� � ����������� ���� ���� </summary>
	void RequestSelectById();
	///<summary> ������ � ����������� ������ ������ �� ������ ����� � ������� </summary>
	void RequestSelectAll();
	///<summary> �������� ������������ �� ���� ����� � ������� ���� ����������������� ����� </summary>
	void RequestUpdate();
	///<summary> ������� ������ �� ���������� </summary>
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

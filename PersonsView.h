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
	///<summary> ��������� ���� �� ���������� �� ���� �������� ��� ���������� </summary>
	void AssignPerson(PERSONS& recItem);
	///<summary> ������� ������ �� ���������� </summary>
	void InsertPersonRows(CSmartArray<PERSONS>& oPersonsSmartArray)
	{
		for (INT_PTR i = 0; i < oPersonsSmartArray.GetCount(); ++i)
		{
			PERSONS* pRecItem = static_cast<PERSONS*>(oPersonsSmartArray.GetAt(i));

			if (pRecItem != nullptr) {

				int nIndex = static_cast<int>(i);
				CString strHolder;

				strHolder.Format(_T("%d"), pRecItem->nId);
				int row = static_cast<int>(m_pListCtrl->InsertItem(nIndex, strHolder));



				m_pListCtrl->SetItemText(nIndex, 1, CString(pRecItem->szFirstName));

				m_pListCtrl->SetItemText(row, 2, CString(pRecItem->szMiddleName));

				m_pListCtrl->SetItemText(row, 3, CString(pRecItem->szLastName));

				m_pListCtrl->SetItemText(row, 4, CString(pRecItem->szEgn));

				strHolder.Format(_T("%d"), pRecItem->nCityId);
				m_pListCtrl->SetItemText(row, 5, strHolder);

				m_pListCtrl->SetItemText(row, 6, CString(pRecItem->szAddress));

				m_pListCtrl->SetItemData(row, pRecItem->nId);
			}
		}
	}

// Overrides
// ----------------
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
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
};

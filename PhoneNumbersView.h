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
	template <typename tableType>
	void InsertCityRows(CSmartArray<tableType>& oTableTypeArray,
		CMap<int, int, CString, const CString&>& personsMap,
		CMap<int, int, CString, const CString&>& phoneTypesMap
	)
	{
		for (INT_PTR i = 0; i < oTableTypeArray.GetCount(); ++i)
		{
			PHONE_NUMBERS* pRecItem = static_cast<PHONE_NUMBERS*>(oTableTypeArray.GetAt(i));

			if (pRecItem != nullptr) {

				CString strHolder;
				strHolder.Format(_T("%d"), pRecItem->nId);
				int row = static_cast<int>(m_pListCtrl->InsertItem(i, strHolder));

				m_pListCtrl->SetItemData(row, row);

				CString strPersonName;
				if (personsMap.Lookup(pRecItem->nPersonId, strPersonName))
					m_pListCtrl->SetItemText(row, 1, strPersonName);

				CString strPhoneType;
				if (phoneTypesMap.Lookup(pRecItem->nPhoneTypeId, strPhoneType))
					m_pListCtrl->SetItemText(row, 2, strPhoneType);

				m_pListCtrl->SetItemText(row, 3, CString(pRecItem->szPhoneNumber));
			}
		}
		m_pListCtrl->SortItems(CUtils::CompareByName, (LPARAM)m_pListCtrl);
	}

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

// Members
// ----------------
	int m_SelectedIndex = -1;
	CListCtrl* m_pListCtrl;
};


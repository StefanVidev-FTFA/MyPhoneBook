#pragma once
#include "PersonsDoc.h"
#include "CommonListView.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsView
class CPersonsView : public CCommonListView
{
	// Constants
	// ----------------
protected:
	CPersonsView() noexcept;
	DECLARE_DYNCREATE(CPersonsView)

	// Methods
	// ----------------
protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
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
	void AssignPerson(PERSONS& recItem);

public:
	CPersonsDoc* GetDocument() const;
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CPersonsView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void InsertPersonRows(CSmartArray<PERSONS>& oPersonsSmartArray)
	{
		for (INT_PTR i = 0; i < oPersonsSmartArray.GetCount(); ++i)
		{
			PERSONS* pRecItem = static_cast<PERSONS*>(oPersonsSmartArray.GetAt(i));

			if (pRecItem != nullptr) {

				CString strHolder;

				strHolder.Format(_T("%d"), pRecItem->nId);
				int row = m_pListCtrl->InsertItem(i, strHolder);


				m_pListCtrl->SetItemText(i, 1, CString(pRecItem->szFirstName));

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

	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	// Overrides
	// ----------------
protected:
	void CreateListOnInit() override;

	// Members
	// ----------------
protected:
	CListCtrl* m_pListCtrl;
	int m_SelectedIndex = -1;
};

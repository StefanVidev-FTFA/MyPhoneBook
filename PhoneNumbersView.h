#pragma once
#include "CitiesArray.h"
#include "PhoneNumbersDoc.h"
#include "CommonListView.h"

using namespace std;

class CPhoneNumbersView : public CCommonListView
{
protected:
    CPhoneNumbersView() noexcept;
    DECLARE_DYNCREATE(CPhoneNumbersView)

public:
	CPhoneNumbersDoc* GetDocument() const;

    // Overrides
public:
    virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	void CreateListOnInit() override;


public:
	virtual ~CPhoneNumbersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	template <typename tableType>
	void InsertCityRows(CSmartArray<tableType>& oTableTypeArray)
	{
		for (INT_PTR i = 0; i < oTableTypeArray.GetCount(); ++i)
		{
			PHONE_NUMBERS* pRecItem = static_cast<PHONE_NUMBERS*>(oTableTypeArray.GetAt(i));

			if (pRecItem != nullptr) {

				CString strHolder;

				strHolder.Format(_T("%d"), pRecItem->nId);
				int row = m_pListCtrl->InsertItem(i, strHolder);

				strHolder.Format(_T("%d"), pRecItem->nPersonId);
				m_pListCtrl->SetItemText(i, 1, strHolder);

				strHolder.Format(_T("%d"), pRecItem->nPhoneTypeId);
				m_pListCtrl->SetItemText(row, 2, strHolder);

				m_pListCtrl->SetItemText(row, 3, CString(pRecItem->szPhoneNumber));

			}
		}
	}

	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


	// Members
	// ----------------
	CListCtrl* m_pListCtrl;

};
#pragma once

#include "PhoneTypesDoc.h"
#include "CommonListView.h"

using namespace std;

class CPhoneTypesView : public CCommonListView
{
protected:
	CPhoneTypesView() noexcept;
	DECLARE_DYNCREATE(CPhoneTypesView)

public:
	CPhoneTypesDoc* GetDocument() const;

	// Overrides
public:
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	void CreateListOnInit() override;


public:
	virtual ~CPhoneTypesView();
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
			PHONE_TYPES* pRecItem = static_cast<PHONE_TYPES*>(oTableTypeArray.GetAt(i));

			if (pRecItem != nullptr) {

				CString strHolder;

				strHolder.Format(_T("%d"), pRecItem->nId);
				int row = m_pListCtrl->InsertItem(i, strHolder);

				m_pListCtrl->SetItemText(i, 1, CString(pRecItem->szPhoneType));

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
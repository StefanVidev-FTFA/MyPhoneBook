#pragma once
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>

class CPhoneNumbersView : public CCommonListView
{
protected:
    CPhoneNumbersView() noexcept;
    DECLARE_DYNCREATE(CPhoneNumbersView)

public:
	CCitiesDoc* GetDocument() const;

    // Overrides
public:
    virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


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

				CString sId;
				sId.Format(_T("%d"), pRecItem->nId);

				int row = m_pListCtrl->InsertItem(i, sId);
				m_pListCtrl->SetItemText(i, 1, CString(10));
				m_pListCtrl->SetItemText(row, 2, CString(50));

			}
		}
	}

	void SetViewStyle();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


	// Members
	// ----------------
	CListCtrl* m_pListCtrl;

};
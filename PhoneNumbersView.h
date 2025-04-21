#pragma once
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>

class CPhoneNumbersView : public CListView
{
protected:
    CPhoneNumbersView() noexcept;
    DECLARE_DYNCREATE(CPhoneNumbersView)

public:
	CCitiesDoc* GetDocument() const;

    // Overrides
public:
    virtual void OnInitialUpdate();     // Called first time after creation
   // virtual void DoDataExchange(CDataExchange* pDX); // If you plan to bind controls
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


public:
	virtual ~CPhoneNumbersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void SetViewStyle();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


	// Members
	// ----------------
	CListCtrl* m_pListCtrl;

};
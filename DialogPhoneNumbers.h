#pragma once
#include "afxdialogex.h"
#include "CommonListView.h"


// DialogPhoneNumbers dialog

class DialogPhoneNumbers : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPhoneNumbers)

public:
	DialogPhoneNumbers(PHONE_NUMBERS recPhoneNum,
		CCommonListView::DialogMode dialogMode = CCommonListView::DialogModeView,
		CWnd* pParent = nullptr
		);
	virtual ~DialogPhoneNumbers();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();

public:
	CCommonListView::DialogMode m_dialogMode;
	PHONE_NUMBERS m_recPhoneNumForUpdOrIns;
	PHONE_NUMBERS m_recPhoneNumForView;
	CButton m_BtnConfirm;
	CButton m_BtnCancel;
	CEdit m_EditBoxPersonId;
	CEdit m_EditBoxPhoneTypeId;
	CEdit m_EditBoxPhoneNumber;
};

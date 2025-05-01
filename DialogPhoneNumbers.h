#pragma once
#include "CommonListView.h"
#include "afxdialogex.h"
#include "PhoneNumbersInfo.h"


class DialogPhoneNumbers : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPhoneNumbers)

public:
	DialogPhoneNumbers(CPhoneNumbersInfo* oInfo,
		CCommonListView::DialogMode dialogMode = CCommonListView::DialogModeView,
		CWnd* pParent = nullptr);
	virtual ~DialogPhoneNumbers();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();

public:
	CCommonListView::DialogMode m_dialogMode;
	PHONE_NUMBERS m_recPhoneNumForUpdOrIns;
	PHONE_NUMBERS m_recPhoneNumForView;

	CPhoneNumbersInfo* m_pInfo;
	CEdit m_EditBoxPhoneNumber;
	CComboBox m_ComboBoxPhoneTypesIds;
	CButton m_BtnConfirm;
};

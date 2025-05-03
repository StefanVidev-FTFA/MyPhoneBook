#pragma once
#include "CommonListView.h"
#include "afxdialogex.h"
#include "PhoneNumbersInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogPhoneNumbers
class CDialogPhoneNumbers : public CDialogEx
{
// Constants
// ----------------
	enum { IDD = IDD_PHONE_NUMBERS };

// Defines
// ----------------
	DECLARE_DYNAMIC(CDialogPhoneNumbers)
	DECLARE_MESSAGE_MAP()
// Constructor / Destructor
// ----------------
public:

	CDialogPhoneNumbers(CPhoneNumbersInfo* oInfo,
		CCommonListView::DialogMode dialogMode = CCommonListView::DialogModeView,
		CWnd* pParent = nullptr);
	virtual ~CDialogPhoneNumbers();

	// Methods
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();

	// Members
	// ----------------
public:
	CCommonListView::DialogMode m_dialogMode;
	PHONE_NUMBERS m_recPhoneNumForUpdOrIns;
	PHONE_NUMBERS m_recPhoneNumForView;
	CPhoneNumbersInfo* m_pInfo;

	CEdit m_edbPhoneNumber;
	CComboBox m_cmbPhoneTypesIds;
	CButton m_btnConfirm;
};

#pragma once
#include "CommonListView.h"
#include "afxdialogex.h"
#include "PhoneNumbersInfo.h"
#include "BaseDialog.h"


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
		DialogMode dialogMode = DialogModeView,
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
	DialogMode m_dialogMode;
	PHONE_NUMBERS m_recPhoneNumForUpdOrIns;
	PHONE_NUMBERS m_recPhoneNumForView;
	CPhoneNumbersInfo* m_pInfo;

	CEdit m_edbPhoneNumber;
	CComboBox m_cmbPhoneTypesIds;
	CButton m_btnConfirm;
};

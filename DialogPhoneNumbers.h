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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS };
#endif

	// Constructor / Destructor
	// ----------------
public:
	DECLARE_DYNAMIC(CDialogPhoneNumbers)
	CDialogPhoneNumbers(CPhoneNumbersInfo* oInfo,
		CCommonListView::DialogMode dialogMode = CCommonListView::DialogModeView,
		CWnd* pParent = nullptr);
	virtual ~CDialogPhoneNumbers();

	// Methods
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();

	// Members
	// ----------------
public:
	CCommonListView::DialogMode m_dialogMode;
	PHONE_NUMBERS m_recPhoneNumForUpdOrIns;
	PHONE_NUMBERS m_recPhoneNumForView;

	CPhoneNumbersInfo* m_pInfo;
	CEdit m_EditBoxPhoneNumber;
	CComboBox m_ComboBoxPhoneTypesIds;
	CButton m_BtnConfirm;
};

#pragma once
#include "afxdialogex.h"
#include "PhoneTypes.h"
#include "CommonListView.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogPhoneTypes
class CDialogPhoneTypes : public CDialogEx
{
// Constants
// ----------------
	enum { IDD = IDD_DIALOG7 };

// Defines
// ----------------
	DECLARE_DYNAMIC(CDialogPhoneTypes)
	DECLARE_MESSAGE_MAP()
// Constructor / Destructor
// ----------------
public:

	CDialogPhoneTypes(CWnd* pParent = nullptr,
		CCommonListView::DialogMode dialogMode = CCommonListView::DialogModeView,
		CString strPhoneType = _T("")
	);
	virtual ~CDialogPhoneTypes();

	// Methods
	// ----------------
public:
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	// Members
	// ----------------
public:
	PHONE_TYPES m_recPhoneTypeForUpdOrIns;
	CCommonListView::DialogMode m_dialogMode;
	CEdit m_EditBoxPhoneTypesField;
	CString m_strPhoneType;
	CButton m_ButtonPtsConfirm;
};

#pragma once
#include "afxdialogex.h"
#include "PhoneTypes.h"


// DialogUpdOrInsPhoneType dialog

class DialogUpdOrInsPhoneType : public CDialogEx
{
	DECLARE_DYNAMIC(DialogUpdOrInsPhoneType)

public:
	DialogUpdOrInsPhoneType(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogUpdOrInsPhoneType();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();

public:
	PHONE_TYPES m_recPhoneTypeForUpdOrIns;
	CEdit m_EditBoxPhoneTypesField;
};

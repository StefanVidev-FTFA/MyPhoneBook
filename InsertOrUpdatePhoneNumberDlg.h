#pragma once
#include "afxdialogex.h"
#include "PhoneNumbers.h"


// InsertOrUpdatePhoneNumberDlg dialog

class InsertOrUpdatePhoneNumberDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InsertOrUpdatePhoneNumberDlg)

public:
	InsertOrUpdatePhoneNumberDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~InsertOrUpdatePhoneNumberDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();

public:
	PHONE_NUMBERS m_recPhoneNumForInsertOrUpdate;
	CEdit m_EditBoxPersonId;
	CEdit m_EditBoxPhoneTypeId;
	CEdit m_EditBoxPhoneNumber;
};

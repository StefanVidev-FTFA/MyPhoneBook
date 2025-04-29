#pragma once
#include "afxdialogex.h"


// DialogSelectRecordPhoneType dialog

class DialogSelectRecordPhoneType : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSelectRecordPhoneType)

public:
	DialogSelectRecordPhoneType(CWnd* pParent = nullptr,CString strPhoneType = _T(""));   // standard constructor
	virtual ~DialogSelectRecordPhoneType();

	afx_msg void OnClickedButtonClose();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_PHONE_TYPE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CString m_strPhoneType;
public:
	CStatic m_textSelectedPhoneType;
};

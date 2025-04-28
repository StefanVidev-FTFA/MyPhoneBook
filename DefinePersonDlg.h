#pragma once
#include "afxdialogex.h"


// DefinePersonDlg dialog

class DefinePersonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DefinePersonDlg)

public:
	DefinePersonDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DefinePersonDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

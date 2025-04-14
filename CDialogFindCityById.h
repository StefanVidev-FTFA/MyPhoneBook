#pragma once
#include "afxdialogex.h"


// CDialogFindCityById dialog

class CDialogFindCityById : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogFindCityById)

public:
	CDialogFindCityById(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogFindCityById();
	int m_nIdToBeSelected = -1;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedFindByIdCancel();
	afx_msg void OnBnClickedFindByIdFind();
	CEdit m_FindByIdEditField;
	CStatic m_FindCityHeader;
};

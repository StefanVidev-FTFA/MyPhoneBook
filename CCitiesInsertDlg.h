#pragma once
#include "afxdialogex.h"


// CCitiesInsertDlg dialog

class CCitiesData; // forward declaration

class CCitiesInsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCitiesInsertDlg)
	
public:
	//CCitiesInsertDlg(CWnd* pParent);   // standard constructor
	CCitiesInsertDlg(CWnd* pParent=nullptr,CCitiesData* oCitiesData=nullptr, int nTypeOfData=-1,int nIdForUpdate=-1);   // standard constructor
	virtual ~CCitiesInsertDlg();

	CCitiesData* m_oCitiesData;// adding this line result in errors
	int m_nTypeOfCall;
	int m_nIdForUpdate;
	CStatic m_staticMessage;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonCancel();
	CEdit m_EditBoxCity;
	CEdit m_EditBoxRegion;
};

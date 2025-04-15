#pragma once
#include "afxdialogex.h"
#include "Cities.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesInsertDlg

/// <summary> Клас служещ за диалога между потребителя ори въвеждане или обновяване на град /// </summary>
class CCitiesInsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCitiesInsertDlg)
	
	// Constructor / Destructor
	// ----------------
public:
	CCitiesInsertDlg(CWnd* pParent=nullptr,int nMode = -1);
	virtual ~CCitiesInsertDlg();

	// Methods
	// ----------------
protected:
	DECLARE_MESSAGE_MAP()

	// Overrides
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonCancel();

	// Members
	// ----------------
public:
	CEdit m_EditBoxCity;
	CEdit m_EditBoxRegion;
	int m_nMode;
	CITIES m_recCityForUpdate;
};

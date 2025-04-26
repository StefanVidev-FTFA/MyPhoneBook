#pragma once
#include "afxdialogex.h"
#include "Cities.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesInsertOrUpdateDialog

/// <summary> Клас служещ за диалога между потребителя ори въвеждане или обновяване на град /// </summary>
class CCitiesInsertOrUpdateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCitiesInsertOrUpdateDialog)
	
	// Constructor / Destructor
	// ----------------
public:
	CCitiesInsertOrUpdateDialog(CWnd* pParent=nullptr);
	virtual ~CCitiesInsertOrUpdateDialog();

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
	CITIES m_recCityForInsertOrUpdate;
	CString m_strCityName;
	CString m_strCityRegion;
};

#pragma once
#include "afxdialogex.h"
#include "Cities.h"
#include "CommonListView.h"
#include "BaseDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogCities
class CDialogCities : public CDialogEx
{
// Constants
// ----------------
	enum { IDD = IDD_CITIES };

// Defines
// ----------------
DECLARE_MESSAGE_MAP()
DECLARE_DYNAMIC(CDialogCities)

// Constructor / Destructor
// ----------------
public:
	CDialogCities(CITIES recCity,
		DialogMode dialogMode = DialogModeView,
		CWnd* pParent = nullptr);

	virtual ~CDialogCities();

// Overrides
// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

// Methods
// ----------------
public:
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();

// Members
// ----------------
public:
	DialogMode m_dialogMode;
	CITIES m_recCityForInsertOrUpdate;
	CITIES m_recCityForView;

	CButton m_btnCancel;
	CButton m_btnConfirm;
	CEdit m_edbCityName;
	CEdit m_edbCityRegion;
};

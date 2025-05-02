#pragma once
#include "afxdialogex.h"
#include "Cities.h"
#include "CommonListView.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogCities

class CDialogCities : public CDialogEx
{
	// Constants
	// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES };
#endif

	// Constructor / Destructor
	// ----------------
public:
	DECLARE_DYNAMIC(CDialogCities)
	CDialogCities(CITIES recCity,
		CCommonListView::DialogMode dialogMode = CCommonListView::DialogModeView,
		CWnd* pParent = nullptr
		); 
	virtual ~CDialogCities();

	// Methods
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();

	// Members
	// ----------------
public:
	CCommonListView::DialogMode m_dialogMode;
	CITIES m_recCityForInsertOrUpdate;
	CITIES m_recCityForView;
	CButton m_BtnCancel;
	CButton m_BtnConfirm;
	CEdit m_EditboxCityName;
	CEdit m_EditboxCityRegion;
};

#pragma once
#include "afxdialogex.h"
#include "Cities.h"
#include "CommonListView.h"


// CDialogCities dialog

class CDialogCities : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCities)

public:
	CDialogCities(CWnd* pParent = nullptr,
		CCommonListView::DialogMode dialogMode = CCommonListView::DialogModeView,
		CITIES recCity);   // standard constructor
	virtual ~CDialogCities();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


public:
	CCommonListView::DialogMode m_dialogMode;
	CITIES m_recCityForInsertOrUpdate;
	CITIES m_recCityForView;
	CButton m_BtnCancel;
	CButton m_BtnConfirm;
	CEdit m_EditboxCityName;
	CEdit m_EditboxCityRegion;
};

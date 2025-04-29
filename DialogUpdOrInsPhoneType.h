#pragma once
#include "afxdialogex.h"
#include "PhoneTypes.h"
#include "CommonListView.h"

class DialogUpdOrInsPhoneType : public CDialogEx
{
	DECLARE_DYNAMIC(DialogUpdOrInsPhoneType)

public:
	DialogUpdOrInsPhoneType(CWnd* pParent = nullptr,
		CCommonListView::DialogMode dialogMode = CCommonListView::DialogModeView,
		CString strPhoneType = _T("")
	);
	virtual ~DialogUpdOrInsPhoneType();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();


public:
	PHONE_TYPES m_recPhoneTypeForUpdOrIns;
	CCommonListView::DialogMode m_dialogMode;
	CEdit m_EditBoxPhoneTypesField;
	CString m_strPhoneType;
	CButton m_ButtonPtsConfirm;
};

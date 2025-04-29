// DialogUpdOrInsPhoneType.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogUpdOrInsPhoneType.h"
#include "Macros.h"

IMPLEMENT_DYNAMIC(DialogUpdOrInsPhoneType, CDialogEx)

DialogUpdOrInsPhoneType::DialogUpdOrInsPhoneType(CWnd* pParent /*=nullptr*/, CCommonListView::DialogMode dialogMod,CString strPhoneType)
	: CDialogEx(IDD_DIALOG7, pParent),m_dialogMode(dialogMod),m_strPhoneType(strPhoneType)
{

}

DialogUpdOrInsPhoneType::~DialogUpdOrInsPhoneType()
{
}

void DialogUpdOrInsPhoneType::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PTS_PHONE_TYPE_BOX, m_EditBoxPhoneTypesField);
	DDX_Control(pDX, BTN_PTS_CONFIRM, m_ButtonPtsConfirm);
}

BOOL DialogUpdOrInsPhoneType::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_dialogMode == CCommonListView::DialogModeView)
	{
		m_EditBoxPhoneTypesField.SetReadOnly(true);
		m_EditBoxPhoneTypesField.SetWindowTextW(m_strPhoneType);
		m_ButtonPtsConfirm.EnableWindow(false);
	}
	else
	{
		m_EditBoxPhoneTypesField.SetReadOnly(false);
		m_ButtonPtsConfirm.EnableWindow(true);
	}

	return TRUE;
}


BEGIN_MESSAGE_MAP(DialogUpdOrInsPhoneType, CDialogEx)
	ON_BN_CLICKED(BTN_PTS_CONFIRM, &DialogUpdOrInsPhoneType::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PTS_CANCEL, &DialogUpdOrInsPhoneType::OnClickedButtonCancel)
END_MESSAGE_MAP()


void DialogUpdOrInsPhoneType::OnClickedButtonConfirm()
{
	CString strPhoneType;
	m_EditBoxPhoneTypesField.GetWindowText(strPhoneType);

	m_recPhoneTypeForUpdOrIns.nUpdateCounter = 0;
	wcscpy_s(m_recPhoneTypeForUpdOrIns.szPhoneType, strPhoneType);

	EndDialog(IDOK);
}

void DialogUpdOrInsPhoneType::OnClickedButtonCancel()
{
	EndDialog(IDOK);
}

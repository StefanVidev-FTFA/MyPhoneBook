// DialogUpdOrInsPhoneType.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogUpdOrInsPhoneType.h"
#include "Macros.h"


// DialogUpdOrInsPhoneType dialog

IMPLEMENT_DYNAMIC(DialogUpdOrInsPhoneType, CDialogEx)

DialogUpdOrInsPhoneType::DialogUpdOrInsPhoneType(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

DialogUpdOrInsPhoneType::~DialogUpdOrInsPhoneType()
{
}

void DialogUpdOrInsPhoneType::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PTS_PHONE_TYPE_BOX, m_EditBoxPhoneTypesField);
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

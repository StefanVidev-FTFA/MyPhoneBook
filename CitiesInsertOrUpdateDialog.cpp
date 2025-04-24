#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CitiesInsertOrUpdateDialog.h"
#include "CitiesView.h"

IMPLEMENT_DYNAMIC(CCitiesInsertOrUpdateDialog, CDialogEx)

CCitiesInsertOrUpdateDialog::CCitiesInsertOrUpdateDialog(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

CCitiesInsertOrUpdateDialog::~CCitiesInsertOrUpdateDialog(){}

void CCitiesInsertOrUpdateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, EDB_DLG1_CITY_NAME, m_EditBoxCity);
	DDX_Control(pDX, EDB_DLG1_CITY_REGION, m_EditBoxRegion);
}

BEGIN_MESSAGE_MAP(CCitiesInsertOrUpdateDialog, CDialogEx)
	ON_BN_CLICKED(BTN_INSERT_OR_UPDATE, &CCitiesInsertOrUpdateDialog::OnClickedButtonInsert)
	ON_BN_CLICKED(BTN_DLG1_CANCEL, &CCitiesInsertOrUpdateDialog::OnClickedButtonCancel)
END_MESSAGE_MAP()

void CCitiesInsertOrUpdateDialog::OnClickedButtonInsert()
{
	m_EditBoxCity.GetWindowText(m_strCityName);
	m_EditBoxRegion.GetWindowText(m_strCityRegion);

	EndDialog(IDOK);
}

void CCitiesInsertOrUpdateDialog::OnClickedButtonCancel()
{
	EndDialog(IDOK);
}

// InsertOrUpdatePhoneNumberDlg.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "InsertOrUpdatePhoneNumberDlg.h"
#include "Macros.h"


// InsertOrUpdatePhoneNumberDlg dialog

IMPLEMENT_DYNAMIC(InsertOrUpdatePhoneNumberDlg, CDialogEx)

InsertOrUpdatePhoneNumberDlg::InsertOrUpdatePhoneNumberDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{

}

InsertOrUpdatePhoneNumberDlg::~InsertOrUpdatePhoneNumberDlg()
{
	//m_EditBoxPersonId
}

void InsertOrUpdatePhoneNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PNS_PERSON_ID, m_EditBoxPersonId);
	DDX_Control(pDX, STT_PNS_PHONE_TYPE_ID, m_EditBoxPhoneTypeId);
	DDX_Control(pDX, STT_PNS_PHONE_NUMBER, m_EditBoxPhoneNumber);
}


BEGIN_MESSAGE_MAP(InsertOrUpdatePhoneNumberDlg, CDialogEx)
	ON_BN_CLICKED(BTN_PNS_INSERT_OR_UPDATE_CONFIRM, &InsertOrUpdatePhoneNumberDlg::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PNS_INSERT_OR_UPDATE_CANCEL, &InsertOrUpdatePhoneNumberDlg::OnClickedButtonCancel)
END_MESSAGE_MAP()


void InsertOrUpdatePhoneNumberDlg::OnClickedButtonConfirm()
{
	m_recPhoneNumForInsertOrUpdate.nUpdateCounter = 0;

	CString strPersonId;
	m_EditBoxPersonId.GetWindowText(strPersonId	);

	CString strPhoneTypeId;
	m_EditBoxPhoneTypeId.GetWindowText(strPhoneTypeId);

	CString strPhoneNumber;
	m_EditBoxPhoneNumber.GetWindowText(strPhoneNumber);

	m_recPhoneNumForInsertOrUpdate.nPersonId = _ttoi(strPersonId);
	m_recPhoneNumForInsertOrUpdate.nPhoneTypeId = _ttoi(strPhoneTypeId);
	wcscpy_s(m_recPhoneNumForInsertOrUpdate.szPhoneNumber, strPhoneNumber);


	EndDialog(IDOK);
}

void InsertOrUpdatePhoneNumberDlg::OnClickedButtonCancel()
{
	EndDialog(IDOK);
}

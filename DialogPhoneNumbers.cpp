// DialogPhoneNumbers.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogPhoneNumbers.h"


IMPLEMENT_DYNAMIC(DialogPhoneNumbers, CDialogEx)

DialogPhoneNumbers::DialogPhoneNumbers(PHONE_NUMBERS recPhoneNum,
	CCommonListView::DialogMode dialogMod, CWnd* pParent)
	: CDialogEx(IDD_PHONE_NUMBERS, pParent), m_dialogMode(dialogMod), m_recPhoneNumForView(recPhoneNum)
{

}

DialogPhoneNumbers::~DialogPhoneNumbers()
{
}

BOOL DialogPhoneNumbers::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_dialogMode == CCommonListView::DialogModeView)
	{

		m_EditBoxPersonId.SetReadOnly(true);
		m_EditBoxPhoneTypeId.SetReadOnly(true);
		m_EditBoxPhoneNumber.SetReadOnly(true);

		CString strId;

		strId.Format(_T("%d"), m_recPhoneNumForView.nPersonId);
		m_EditBoxPersonId.SetWindowTextW(strId);

		strId.Format(_T("%d"), m_recPhoneNumForView.nPhoneTypeId);
		m_EditBoxPhoneTypeId.SetWindowTextW(strId);

		m_EditBoxPhoneNumber.SetWindowTextW(CString(m_recPhoneNumForView.szPhoneNumber));

		m_BtnConfirm.EnableWindow(false);
	}
	else
	{

		m_EditBoxPersonId.SetReadOnly(false);
		m_EditBoxPhoneTypeId.SetReadOnly(false);
		m_EditBoxPhoneNumber.SetReadOnly(false);

		CString strId;

		strId.Format(_T("%d"), m_recPhoneNumForView.nPersonId);
		m_EditBoxPersonId.SetWindowTextW(strId);

		strId.Format(_T("%d"), m_recPhoneNumForView.nPhoneTypeId);
		m_EditBoxPhoneTypeId.SetWindowTextW(strId);

		m_EditBoxPhoneNumber.SetWindowTextW(CString(m_recPhoneNumForView.szPhoneNumber));

		m_BtnConfirm.EnableWindow(true);
	}

	return TRUE;
}

void DialogPhoneNumbers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, BTN_PNS_CONFIRM, m_BtnConfirm);
	DDX_Control(pDX, BTN_PNS_CANCEL, m_BtnCancel);
	DDX_Control(pDX, STT_PNS_PERSON_ID, m_EditBoxPersonId);
	DDX_Control(pDX, STT_PNS_PHONE_TYPE_ID, m_EditBoxPhoneTypeId);
	DDX_Control(pDX, STT_PNS_PHONE_NUMBER, m_EditBoxPhoneNumber);
}


BEGIN_MESSAGE_MAP(DialogPhoneNumbers, CDialogEx)
	ON_BN_CLICKED(BTN_PNS_CONFIRM, &DialogPhoneNumbers::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PNS_CANCEL, &DialogPhoneNumbers::OnClickedButtonCancel)
END_MESSAGE_MAP()


void DialogPhoneNumbers::OnClickedButtonConfirm()
{
	CString strId;

	m_EditBoxPersonId.GetWindowText(strId);
	m_recPhoneNumForUpdOrIns.nPersonId = _ttoi(strId);

	m_EditBoxPhoneTypeId.GetWindowText(strId);
	m_recPhoneNumForUpdOrIns.nPhoneTypeId = _ttoi(strId);

	CString strNumber;
	m_EditBoxPhoneNumber.GetWindowText(strNumber);

	wcscpy_s(m_recPhoneNumForUpdOrIns.szPhoneNumber, MAX_PHONE_NUMBER, strNumber);

	EndDialog(IDOK);
}

void DialogPhoneNumbers::OnClickedButtonCancel()
{
	EndDialog(IDCLOSE);
}


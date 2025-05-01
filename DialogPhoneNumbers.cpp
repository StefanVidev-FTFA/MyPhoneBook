#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogPhoneNumbers.h"
#include "PhoneNumbersInfo.h"
#include "CommonListView.h"



IMPLEMENT_DYNAMIC(DialogPhoneNumbers, CDialogEx)

DialogPhoneNumbers::DialogPhoneNumbers(CPhoneNumbersInfo* oInfo,
	CCommonListView::DialogMode dialogMod, CWnd* pParent)
	: CDialogEx(IDD_PHONE_NUMBERS, pParent), m_dialogMode(dialogMod), m_pInfo(oInfo)
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
		m_EditBoxPhoneNumber.SetReadOnly(true);


		m_EditBoxPhoneNumber.SetWindowTextW(CString(m_pInfo->m_recPhoneNum.szPhoneNumber));

		m_BtnConfirm.EnableWindow(false);

		m_ComboBoxPersonIds.ResetContent();
		CString strPersonId;
		strPersonId.Format(_T("%d"), m_pInfo->m_recPhoneNum.nPersonId);
		m_ComboBoxPersonIds.AddString(strPersonId);
		m_ComboBoxPersonIds.SetCurSel(0);
		m_ComboBoxPersonIds.EnableWindow(false);

		m_ComboBoxPhoneTypesIds.ResetContent();
		CString strPhoneTypeId;
		strPhoneTypeId.Format(_T("%d"), m_pInfo->m_recPhoneNum.nPhoneTypeId);
		m_ComboBoxPhoneTypesIds.AddString(strPhoneTypeId);
		m_ComboBoxPhoneTypesIds.SetCurSel(0);
		m_ComboBoxPhoneTypesIds.EnableWindow(false);
	}

	else
	{
		m_EditBoxPhoneNumber.SetReadOnly(false);
		m_EditBoxPhoneNumber.SetWindowTextW(CString(m_recPhoneNumForView.szPhoneNumber));
		m_BtnConfirm.EnableWindow(true);
		m_ComboBoxPersonIds.ResetContent();

	}

	return TRUE;
}

void DialogPhoneNumbers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PNS_PHONE_NUMBER, m_EditBoxPhoneNumber);
	DDX_Control(pDX, CMB_PNS_PERSONS_IDS, m_ComboBoxPersonIds);
	DDX_Control(pDX, CMB_PNS_PHONE__TYPES_IDS, m_ComboBoxPhoneTypesIds);
	DDX_Control(pDX, BTN_PNS_CONFIRM, m_BtnConfirm);
}


BEGIN_MESSAGE_MAP(DialogPhoneNumbers, CDialogEx)
	ON_BN_CLICKED(BTN_PNS_CONFIRM, &DialogPhoneNumbers::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PNS_CANCEL, &DialogPhoneNumbers::OnClickedButtonCancel)
END_MESSAGE_MAP()


void DialogPhoneNumbers::OnClickedButtonConfirm()
{
	CString strId;

	CString strNumber;
	m_EditBoxPhoneNumber.GetWindowText(strNumber);

	CString strPersonId;
	int nPersonIndex = m_ComboBoxPersonIds.GetCurSel();
	if (nPersonIndex != CB_ERR)
	{
		m_ComboBoxPersonIds.GetLBText(nPersonIndex, strId);
	}
	int nPersonId = _ttoi(strId);

	CString strPhoneTypeId;
	int nPhoneTypeIndex = m_ComboBoxPhoneTypesIds.GetCurSel();
	if (nPhoneTypeIndex != CB_ERR)
	{
		m_ComboBoxPhoneTypesIds.GetLBText(nPhoneTypeIndex, strId);
	}
	int nPhoneTypeId = _ttoi(strId);


	m_recPhoneNumForUpdOrIns.nPersonId = nPersonId;
	m_recPhoneNumForUpdOrIns.nPhoneTypeId = nPhoneTypeId;
	wcscpy_s(m_recPhoneNumForUpdOrIns.szPhoneNumber, MAX_PHONE_NUMBER, strNumber);

	EndDialog(IDOK);
}

void DialogPhoneNumbers::OnClickedButtonCancel()
{
	EndDialog(IDCLOSE);
}


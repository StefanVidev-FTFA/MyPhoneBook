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

		m_ComboBoxPhoneTypesIds.ResetContent();

		CString strType;
		for (INT_PTR i = 0; i < m_pInfo->m_phoneTypesArray.GetCount(); i++)
		{
			if (m_pInfo->m_phoneTypesArray.GetAt(i)->nId == m_pInfo->m_recPhoneNum.nPhoneTypeId)
			{
				strType = CString(m_pInfo->m_phoneTypesArray.GetAt(i)->szPhoneType);
			}
		}

		m_ComboBoxPhoneTypesIds.AddString(strType);
		m_ComboBoxPhoneTypesIds.SetCurSel(0);
		m_ComboBoxPhoneTypesIds.EnableWindow(false);
	}

	else
	{
		m_EditBoxPhoneNumber.SetReadOnly(false);
		m_EditBoxPhoneNumber.SetWindowTextW(CString(m_pInfo->m_recPhoneNum.szPhoneNumber));
		m_BtnConfirm.EnableWindow(true);

		int index = 0;
		for (INT_PTR i = 0; i < m_pInfo->m_phoneTypesArray.GetCount(); i++)
		{
			if (m_pInfo->m_phoneTypesArray.GetAt(i)->nId == m_pInfo->m_recPhoneNum.nPhoneTypeId)
			{
				index = i;
			}
			CString strItem =CString(m_pInfo->m_phoneTypesArray.GetAt(i)->szPhoneType);
			m_ComboBoxPhoneTypesIds.AddString(strItem);
		}
		m_ComboBoxPhoneTypesIds.SetCurSel(index);

	}

	return TRUE;
}

void DialogPhoneNumbers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PNS_PHONE_NUMBER, m_EditBoxPhoneNumber);
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

	CString strPhoneTypeId;
	int nPhoneTypeIndex = m_ComboBoxPhoneTypesIds.GetCurSel();
	if (nPhoneTypeIndex != CB_ERR)
	{
		m_ComboBoxPhoneTypesIds.GetLBText(nPhoneTypeIndex, strId);
	}
	int nPhoneTypeId = _ttoi(strId);


	m_recPhoneNumForUpdOrIns.nPersonId = -1;
	m_recPhoneNumForUpdOrIns.nPhoneTypeId = nPhoneTypeId;
	wcscpy_s(m_recPhoneNumForUpdOrIns.szPhoneNumber, MAX_PHONE_NUMBER, strNumber);

	EndDialog(IDOK);
}

void DialogPhoneNumbers::OnClickedButtonCancel()
{
	EndDialog(IDCLOSE);
}


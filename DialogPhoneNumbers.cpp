#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogPhoneNumbers.h"
#include "PhoneNumbersInfo.h"
#include "CommonListView.h"


// Defines
// ----------------
IMPLEMENT_DYNAMIC(CDialogPhoneNumbers, CDialogEx)
BEGIN_MESSAGE_MAP(CDialogPhoneNumbers, CDialogEx)
	ON_BN_CLICKED(BTN_PNS_CONFIRM, &CDialogPhoneNumbers::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PNS_CANCEL, &CDialogPhoneNumbers::OnClickedButtonCancel)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CDialogPhoneNumbers::CDialogPhoneNumbers(CPhoneNumbersInfo* oInfo,
	CCommonListView::DialogMode dialogMod, CWnd* pParent)
	: CDialogEx(IDD_PHONE_NUMBERS, pParent), m_dialogMode(dialogMod), m_pInfo(oInfo)
{
}
CDialogPhoneNumbers::~CDialogPhoneNumbers()
{
}

// Methods
// ----------------
void CDialogPhoneNumbers::OnClickedButtonConfirm()
{
	CString strId;

	CString strNumber;
	m_EditBoxPhoneNumber.GetWindowText(strNumber);


	int nSelected = m_ComboBoxPhoneTypesIds.GetCurSel();
	int nPhoneTypeId = m_pInfo->m_phoneTypesArray.GetAt(nSelected)->nId;

	m_recPhoneNumForUpdOrIns.nPersonId = -1;
	m_recPhoneNumForUpdOrIns.nPhoneTypeId = nPhoneTypeId;
	wcscpy_s(m_recPhoneNumForUpdOrIns.szPhoneNumber, MAX_PHONE_NUMBER, strNumber);

	EndDialog(IDOK);
}
void CDialogPhoneNumbers::OnClickedButtonCancel()
{
	EndDialog(IDCLOSE);
}

// Overrides
// ----------------
BOOL CDialogPhoneNumbers::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_EditBoxPhoneNumber.SetLimitText(MAX_PHONE_NUMBER-1);

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
void CDialogPhoneNumbers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PNS_PHONE_NUMBER, m_EditBoxPhoneNumber);
	DDX_Control(pDX, CMB_PNS_PHONE__TYPES_IDS, m_ComboBoxPhoneTypesIds);
	DDX_Control(pDX, BTN_PNS_CONFIRM, m_BtnConfirm);
}



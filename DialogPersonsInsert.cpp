#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogPersonsInsert.h"
#include "Macros.h"
#include "PhoneNumbersInfo.h"
#include "DialogPhoneNumbers.h"


IMPLEMENT_DYNAMIC(CDialogPersonsInsert, CDialogEx)

CDialogPersonsInsert::CDialogPersonsInsert(const CSmartArray<CITIES>& oCitiesArray,
	CSmartArray<PHONE_NUMBERS>& phoneNumbers
	,PERSONS recPersonView,bool isReadOnly,bool fillOut, CWnd* pParent)
	: CDialogEx(IDD_PERSONS_DEFINE, pParent), m_oCitiesArray(oCitiesArray),
	 m_oPhoneNumbersArray(phoneNumbers),
	m_recPersonToFillOut(recPersonView), m_isReadOnly(isReadOnly),m_fillOut(fillOut)
{
}

CDialogPersonsInsert::~CDialogPersonsInsert()
{
}

void CDialogPersonsInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PERSONS_FNAME, m_EditBoxFirstName);
	DDX_Control(pDX, STT_PERSONS_MNAME, m_EditBoxMiddleName);
	DDX_Control(pDX, STT_PERSONS_LNAME, m_EditBoxLastName);
	DDX_Control(pDX, STT_PERSONS_EGN, m_EditBoxEgn);
	DDX_Control(pDX, STT_PERSONS_ADRESS, m_EditBoxAdress);
	DDX_Control(pDX, CMB_PERSONS_CITY_ID, m_ComboBoxCityId);
	DDX_Control(pDX, BTN_PERSONS_INSERT_CONFIRM, m_ButtonPersonsConfirm);
	DDX_Control(pDX, LSC_PERSONS_PHONE_NUMBERS, m_ListControlPhoneNumbers);
}

BOOL CDialogPersonsInsert::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	int nDefaultIndex = 0;
	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		CString strItem;
		strItem.Format(_T("  %s, %s"),
			CString(m_oCitiesArray.GetAt(i)->szCityName), CString(m_oCitiesArray.GetAt(i)->szRegion));

		m_ComboBoxCityId.AddString(strItem);

		CString oke;

		if (m_recPersonToFillOut.nId != 0 
			&& m_recPersonToFillOut.nCityId == m_oCitiesArray.GetAt(i)->nId)
		{
			nDefaultIndex = i;
		}
	}

	m_ComboBoxCityId.SetCurSel(nDefaultIndex);

	if (m_fillOut) 
	{
		m_EditBoxFirstName.SetWindowText(m_recPersonToFillOut.szFirstName);
		m_EditBoxMiddleName.SetWindowText(m_recPersonToFillOut.szMiddleName);
		m_EditBoxLastName.SetWindowText(m_recPersonToFillOut.szLastName);
		m_EditBoxEgn.SetWindowText(m_recPersonToFillOut.szEgn);
		m_EditBoxAdress.SetWindowText(m_recPersonToFillOut.szAddress);

		FillPhones();
	}

	if(m_isReadOnly)
	{
		m_EditBoxFirstName.EnableWindow(false);
		m_EditBoxMiddleName.EnableWindow(false);
		m_EditBoxLastName.EnableWindow(false);
		m_EditBoxEgn.EnableWindow(false);
		m_EditBoxAdress.EnableWindow(false);
		m_ComboBoxCityId.EnableWindow(false);

		m_ButtonPersonsConfirm.EnableWindow(false);
	}

	m_ListControlPhoneNumbers.InsertColumn(0, _T("Phone Number"), LVCFMT_LEFT, 160);
	m_ListControlPhoneNumbers.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;
}

void CDialogPersonsInsert::FillPhones()
{
	for (INT_PTR i = 0; i < m_oPhoneNumbersArray.GetCount(); i++)
	{
		CString strPhoneNumber = CString(m_oPhoneNumbersArray.GetAt(i)->szPhoneNumber);
		int nIndex = m_ListControlPhoneNumbers.InsertItem(i, strPhoneNumber);
	}
}


BEGIN_MESSAGE_MAP(CDialogPersonsInsert, CDialogEx)
	ON_BN_CLICKED(BTN_PERSONS_INSERT_CONFIRM, &CDialogPersonsInsert::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PERSONS_INSERT_CANCEL, &CDialogPersonsInsert::OnClickedButtonCancel)
	ON_NOTIFY(NM_RCLICK, LSC_PERSONS_PHONE_NUMBERS, &CDialogPersonsInsert::OnNMRClickListControl)
	ON_COMMAND(ID_LIST_OPTION1, &CDialogPersonsInsert::InsertPhoneNumber)
	ON_COMMAND(ID_LIST_OPTION2, &CDialogPersonsInsert::EditPhoneNumber)
END_MESSAGE_MAP()


void CDialogPersonsInsert::OnClickedButtonConfirm()
{
	int nIndex = m_ComboBoxCityId.GetCurSel();
	int actualCityId = m_oCitiesArray.GetAt(nIndex)->nId;

	//Utils::MessageWithInt(_T(" the actual City Id: %d"), actualCityId);

	m_recPersonToInsert.nCityId = actualCityId;

	m_EditBoxFirstName.GetWindowText(m_recPersonToInsert.szFirstName, MAX_ANY_NAME);
	m_EditBoxMiddleName.GetWindowText(m_recPersonToInsert.szMiddleName, MAX_ANY_NAME);
	m_EditBoxLastName.GetWindowText(m_recPersonToInsert.szLastName, MAX_ANY_NAME);
	m_EditBoxEgn.GetWindowText(m_recPersonToInsert.szEgn, MAX_EGN);
	m_EditBoxAdress.GetWindowText(m_recPersonToInsert.szAddress, MAX_ADRESS);

	EndDialog(IDOK);
}

void CDialogPersonsInsert::OnClickedButtonCancel()
{
	EndDialog(IDCLOSE);
}

void CDialogPersonsInsert::OnNMRClickListControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	CMenu menu;
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING, ID_LIST_OPTION1, _T("New..."));
	menu.AppendMenu(MF_STRING, ID_LIST_OPTION2, _T("Edit..."));

	CPoint point;
	GetCursorPos(&point);
	menu.TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);

	*pResult = 0;
}

void CDialogPersonsInsert::InsertPhoneNumber()
{
	CPhoneNumbersInfo* pInfo = new CPhoneNumbersInfo();

	CDialogPhoneNumbers oDialog(pInfo, CCommonListView::DialogModeEdit);

	INT_PTR result = oDialog.DoModal();
	if (result == IDOK)
	{
		oDialog.m_recPhoneNumForUpdOrIns.nId = -1;


		oDialog.m_recPhoneNumForUpdOrIns.nPersonId = m_recPersonToFillOut.nId;

		m_oPhoneNumbersArray.Add(new PHONE_NUMBERS(oDialog.m_recPhoneNumForUpdOrIns));

		CString strPhoneNumber = CString(oDialog.m_recPhoneNumForUpdOrIns.szPhoneNumber);
		int nIndex = m_ListControlPhoneNumbers.InsertItem(m_ListControlPhoneNumbers.GetItemCount(), strPhoneNumber);
	}
}

void CDialogPersonsInsert::EditPhoneNumber()
{
	int nSelectedIndex = m_ListControlPhoneNumbers.GetNextItem(-1, LVNI_SELECTED);

	if (nSelectedIndex != -1)
	{
		CString selectedPhoneNumber = m_ListControlPhoneNumbers.GetItemText(nSelectedIndex, 0);
		PHONE_NUMBERS* pPhoneNumber = m_oPhoneNumbersArray.GetAt(nSelectedIndex);

		CPhoneNumbersInfo* pInfo = new CPhoneNumbersInfo();

		pInfo->m_recPhoneNum = *pPhoneNumber;

		CDialogPhoneNumbers oDialog(pInfo, CCommonListView::DialogModeEdit);
		INT_PTR result = oDialog.DoModal();
		if (result == IDOK)
		{
			*pPhoneNumber = oDialog.m_recPhoneNumForUpdOrIns;

			m_ListControlPhoneNumbers.SetItemText(nSelectedIndex, 0, CString(pPhoneNumber->szPhoneNumber));
		}
	}
	else
	{
		MESSAGE_INFO(_T("No phone number selected."));
	}
}



#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogPersons.h"
#include "Macros.h"
#include "PhoneNumbersInfo.h"
#include "DialogPhoneNumbers.h"

// Defines
// ----------------
BEGIN_MESSAGE_MAP(CDialogPersons, CDialogEx)
	ON_BN_CLICKED(BTN_PERSONS_INSERT_CONFIRM, &CDialogPersons::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PERSONS_INSERT_CANCEL, &CDialogPersons::OnClickedButtonCancel)
	ON_NOTIFY(NM_RCLICK, LSC_PERSONS_PHONE_NUMBERS, &CDialogPersons::OnNMRClickListControl)
	ON_COMMAND(ID_LIST_OPTION1, &CDialogPersons::InsertPhoneNumber)
	ON_COMMAND(ID_LIST_OPTION2, &CDialogPersons::EditPhoneNumber)
	ON_COMMAND(ID_LIST_OPTION3, &CDialogPersons::RemovePhoneNumber)
END_MESSAGE_MAP()
IMPLEMENT_DYNAMIC(CDialogPersons, CDialogEx)

// Constructor / Destructor
// ----------------
CDialogPersons::CDialogPersons(const CSmartArray<CITIES>& oCitiesArray,
	CSmartArray<PHONE_NUMBERS>& phoneNumbers,
	PERSONS recPerson,
	bool isReadOnly,
	bool fillOut,
	CWnd* pParent)
	: CDialogEx(IDD_PERSONS_DEFINE, pParent),
	m_oCitiesArray(oCitiesArray),
	m_oPhoneNumbersArray(phoneNumbers),
	m_recPersonToFillOut(recPerson), 
	m_isReadOnly(isReadOnly),
	m_fillOut(fillOut)
{
}
CDialogPersons::~CDialogPersons()
{
}

// Methods
// ----------------
void CDialogPersons::FillPhones()
{
	for (INT_PTR i = 0; i < m_oPhoneNumbersArray.GetCount(); i++)
	{
		CString strPhoneNumber = CString(m_oPhoneNumbersArray.GetAt(i)->szPhoneNumber);
		int nIndex = m_ListControlPhoneNumbers.InsertItem(i, strPhoneNumber);
	}
}
void CDialogPersons::OnClickedButtonConfirm()
{
	int nIndex = m_cmbCities.GetCurSel();
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
void CDialogPersons::OnClickedButtonCancel()
{
	EndDialog(IDCLOSE);
}
void CDialogPersons::InsertPhoneNumber()
{
	CPhoneNumbersInfo* pInfo = new CPhoneNumbersInfo();

	CDialogPhoneNumbers oDialog(pInfo, CCommonListView::DialogModeEdit);

	INT_PTR result = oDialog.DoModal();
	if (result == IDOK)
	{
		oDialog.m_recPhoneNumForUpdOrIns.nPersonId = m_recPersonToFillOut.nId;

		m_oPhoneNumbersArray.Add(new PHONE_NUMBERS(oDialog.m_recPhoneNumForUpdOrIns));

		CString strPhoneNumber = CString(oDialog.m_recPhoneNumForUpdOrIns.szPhoneNumber);
		int nIndex = m_ListControlPhoneNumbers.InsertItem(m_ListControlPhoneNumbers.GetItemCount(), strPhoneNumber);
	}
}
void CDialogPersons::EditPhoneNumber()
{
	int nSelectedIndex = m_ListControlPhoneNumbers.GetNextItem(-1, LVNI_SELECTED);

	if (nSelectedIndex != -1)
	{
		CString selectedPhoneNumber = m_ListControlPhoneNumbers.GetItemText(nSelectedIndex, 0);
		PHONE_NUMBERS* pPhoneNumber = m_oPhoneNumbersArray.GetAt(nSelectedIndex);

		CPhoneNumbersInfo* pInfo = new CPhoneNumbersInfo();

		pInfo->m_recPhoneNum = *pPhoneNumber;

		int nIdHolder = pPhoneNumber->nId;
		int nPersonIdHolder = pPhoneNumber->nPersonId;


		CDialogPhoneNumbers oDialog(pInfo, CCommonListView::DialogModeEdit);
		INT_PTR result = oDialog.DoModal();
		if (result == IDOK)
		{
			*pPhoneNumber = oDialog.m_recPhoneNumForUpdOrIns;

			pPhoneNumber->nId = nIdHolder;
			pPhoneNumber->nPersonId = nPersonIdHolder;

			m_ListControlPhoneNumbers.SetItemText(nSelectedIndex, 0, CString(pPhoneNumber->szPhoneNumber));
		}
	}
	else
	{
		MESSAGE_INFO(_T("No phone number selected."));
	}
}
void CDialogPersons::RemovePhoneNumber()
{
	int nSelectedIndex = m_ListControlPhoneNumbers.GetNextItem(-1, LVNI_SELECTED);

	if (nSelectedIndex != -1)
	{
		PHONE_NUMBERS* pPhoneNumber = m_oPhoneNumbersArray.GetAt(nSelectedIndex);

		CString strMessage= _T("Are you sure you wish to delete this row");

		int nResult = AfxMessageBox(strMessage, MB_YESNO);
		if (nResult == IDYES)
		{
			if (pPhoneNumber != nullptr)
			{
				delete pPhoneNumber;
				m_oPhoneNumbersArray.RemoveAt(nSelectedIndex);


				m_ListControlPhoneNumbers.DeleteItem(nSelectedIndex);
			}
		}
	}
	else
	{
		MESSAGE_INFO(_T("No phone number selected."));
	}
}

// Overrides
// ----------------
void CDialogPersons::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PERSONS_FNAME, m_EditBoxFirstName);
	DDX_Control(pDX, STT_PERSONS_MNAME, m_EditBoxMiddleName);
	DDX_Control(pDX, STT_PERSONS_LNAME, m_EditBoxLastName);
	DDX_Control(pDX, STT_PERSONS_EGN, m_EditBoxEgn);
	DDX_Control(pDX, STT_PERSONS_ADRESS, m_EditBoxAdress);
	DDX_Control(pDX, CMB_PERSONS_CITY_ID, m_cmbCities);
	DDX_Control(pDX, BTN_PERSONS_INSERT_CONFIRM, m_ButtonPersonsConfirm);
	DDX_Control(pDX, LSC_PERSONS_PHONE_NUMBERS, m_ListControlPhoneNumbers);
}
BOOL CDialogPersons::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_EditBoxFirstName.SetLimitText(MAX_ANY_NAME);
	m_EditBoxMiddleName.SetLimitText(MAX_ANY_NAME);
	m_EditBoxLastName.SetLimitText(MAX_ANY_NAME);
	m_EditBoxEgn.SetLimitText(MAX_EGN);
	m_EditBoxAdress.SetLimitText(MAX_ADRESS);

	int nSelectedPersonCityIndex = 0;
	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		CString strItem;
		strItem.Format(_T("  %s, %s"),
			CString(m_oCitiesArray.GetAt(i)->szCityName),
			CString(m_oCitiesArray.GetAt(i)->szRegion));

		m_cmbCities.AddString(strItem);

		if (m_recPersonToFillOut.nId != 0
			&& m_recPersonToFillOut.nCityId == m_oCitiesArray.GetAt(i)->nId)
		{
			nSelectedPersonCityIndex = i;
		}
	}

	m_cmbCities.SetCurSel(nSelectedPersonCityIndex);

	if (m_fillOut)
	{
		m_EditBoxFirstName.SetWindowText(m_recPersonToFillOut.szFirstName);
		m_EditBoxMiddleName.SetWindowText(m_recPersonToFillOut.szMiddleName);
		m_EditBoxLastName.SetWindowText(m_recPersonToFillOut.szLastName);
		m_EditBoxEgn.SetWindowText(m_recPersonToFillOut.szEgn);
		m_EditBoxAdress.SetWindowText(m_recPersonToFillOut.szAddress);

		FillPhones();
	}

	if (m_isReadOnly)
	{
		m_EditBoxFirstName.EnableWindow(false);
		m_EditBoxMiddleName.EnableWindow(false);
		m_EditBoxLastName.EnableWindow(false);
		m_EditBoxEgn.EnableWindow(false);
		m_EditBoxAdress.EnableWindow(false);
		m_cmbCities.EnableWindow(false);

		m_ButtonPersonsConfirm.EnableWindow(false);
	}

	m_ListControlPhoneNumbers.InsertColumn(0, _T("Phone Number"), LVCFMT_LEFT, 160);
	m_ListControlPhoneNumbers.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;
}
void CDialogPersons::OnNMRClickListControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	CMenu menu;
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING, ID_LIST_OPTION1, _T("New..."));
	menu.AppendMenu(MF_STRING, ID_LIST_OPTION2, _T("Edit..."));
	menu.AppendMenu(MF_STRING, ID_LIST_OPTION3, _T("Remove..."));

	CPoint point;
	GetCursorPos(&point);
	menu.TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);

	*pResult = 0;
}



#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogPersonsInsert.h"
#include "Macros.h"


IMPLEMENT_DYNAMIC(DialogPersonsInsert, CDialogEx)

DialogPersonsInsert::DialogPersonsInsert(const CStringList& cityIds, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PERSONS_DEFINE, pParent),m_cityIds(cityIds)
{
}
DialogPersonsInsert::DialogPersonsInsert(const CStringList& cityIds,PERSONS recPersonView, CWnd* pParent)
	: CDialogEx(IDD_PERSONS_DEFINE, pParent), m_cityIds(cityIds), m_recPersonToFillOut(recPersonView)
{

}

DialogPersonsInsert::~DialogPersonsInsert()
{
}

void DialogPersonsInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PERSONS_FNAME, m_EditBoxFirstName);
	DDX_Control(pDX, STT_PERSONS_MNAME, m_EditBoxMiddleName);
	DDX_Control(pDX, STT_PERSONS_LNAME, m_EditBoxLastName);
	DDX_Control(pDX, STT_PERSONS_EGN, m_EditBoxEgn);
	DDX_Control(pDX, STT_PERSONS_ADRESS, m_EditBoxAdress);
	DDX_Control(pDX, CMB_PERSONS_CITY_ID, m_ComboBoxCityId);
}

BOOL DialogPersonsInsert::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	POSITION pos = m_cityIds.GetHeadPosition();
	while (pos != nullptr) {
		const CString& cityId = m_cityIds.GetNext(pos);
		m_ComboBoxCityId.AddString(cityId);
	}

	m_ComboBoxCityId.SetCurSel(0);



	if (m_recPersonToFillOut.nId != 0) 
	{
		m_EditBoxFirstName.SetWindowText(m_recPersonToFillOut.szFirstName);
		m_EditBoxMiddleName.SetWindowText(m_recPersonToFillOut.szMiddleName);
		m_EditBoxLastName.SetWindowText(m_recPersonToFillOut.szLastName);
		m_EditBoxEgn.SetWindowText(m_recPersonToFillOut.szEgn);
		m_EditBoxAdress.SetWindowText(m_recPersonToFillOut.szAddress);

		CString strCityId;
		strCityId.Format(_T("%d"), 100);
	}




	return TRUE;
}


BEGIN_MESSAGE_MAP(DialogPersonsInsert, CDialogEx)
	ON_BN_CLICKED(BTN_PERSONS_INSERT_CONFIRM, &DialogPersonsInsert::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PERSONS_INSERT_CANCEL, &DialogPersonsInsert::OnClickedButtonCancel)
	ON_NOTIFY(NM_RCLICK, LSC_PERSONS_PHONE_NUMBERS, &DialogPersonsInsert::OnNMRClickListControl)
	ON_COMMAND(ID_LIST_OPTION1, &DialogPersonsInsert::OnListOption1)
	ON_COMMAND(ID_LIST_OPTION2, &DialogPersonsInsert::OnListOption2)
END_MESSAGE_MAP()


void DialogPersonsInsert::OnClickedButtonConfirm()
{
	int nIndex = m_ComboBoxCityId.GetCurSel();
	CString strCityId;
	m_ComboBoxCityId.GetLBText(nIndex, strCityId);


	m_recPersonToInsert.nCityId = _ttoi(strCityId);

	m_EditBoxFirstName.GetWindowText(m_recPersonToInsert.szFirstName, MAX_ANY_NAME);
	m_EditBoxMiddleName.GetWindowText(m_recPersonToInsert.szMiddleName, MAX_ANY_NAME);
	m_EditBoxLastName.GetWindowText(m_recPersonToInsert.szLastName, MAX_ANY_NAME);
	m_EditBoxEgn.GetWindowText(m_recPersonToInsert.szEgn, MAX_EGN);
	m_EditBoxAdress.GetWindowText(m_recPersonToInsert.szAddress, MAX_ADRESS);


	EndDialog(IDOK);
}

void DialogPersonsInsert::OnClickedButtonCancel()
{
	EndDialog(IDCLOSE);
}

void DialogPersonsInsert::OnNMRClickListControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	CMenu menu;
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING, ID_LIST_OPTION1, _T("Option 1"));
	menu.AppendMenu(MF_STRING, ID_LIST_OPTION2, _T("Option 2"));

	CPoint point;
	GetCursorPos(&point);
	menu.TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);

	*pResult = 0;
}

void DialogPersonsInsert::OnListOption1()
{
	AfxMessageBox(_T("Option 1 clicked"));
}

void DialogPersonsInsert::OnListOption2()
{
	AfxMessageBox(_T("Option 2 clicked"));
}



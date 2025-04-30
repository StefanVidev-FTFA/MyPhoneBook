#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogPersonsInsert.h"


IMPLEMENT_DYNAMIC(DialogPersonsInsert, CDialogEx)

DialogPersonsInsert::DialogPersonsInsert(const CStringList& cityIds, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PERSONS_DEFINE, pParent),m_cityIds(cityIds)
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

	return TRUE;
}


BEGIN_MESSAGE_MAP(DialogPersonsInsert, CDialogEx)
	ON_BN_CLICKED(BTN_PERSONS_INSERT_CONFIRM, &DialogPersonsInsert::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PERSONS_INSERT_CANCEL, &DialogPersonsInsert::OnClickedButtonCancel)
END_MESSAGE_MAP()


void DialogPersonsInsert::OnClickedButtonConfirm()
{
	EndDialog(IDOK);
}

void DialogPersonsInsert::OnClickedButtonCancel()
{
	EndDialog(IDCLOSE);
}



#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogCities.h"

// Defines
// ----------------
BEGIN_MESSAGE_MAP(CDialogCities, CDialogEx)
	ON_BN_CLICKED(BTN_CITIES_CONFIRM, &CDialogCities::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_CITIES_CANCEL, &CDialogCities::OnClickedButtonCancel)
END_MESSAGE_MAP()
IMPLEMENT_DYNAMIC(CDialogCities, CDialogEx)

// Constructor / Destructor
// ----------------
CDialogCities::CDialogCities(CITIES recCityForView,
	DialogMode dialogMod, CWnd* pParent)
	: CDialogEx(IDD_CITIES, pParent), m_dialogMode(dialogMod), m_recCityForView(recCityForView)
{
}
CDialogCities::~CDialogCities()
{
}

// Methods
// ----------------
void CDialogCities::OnClickedButtonConfirm()
{
	CString strCityName;
	m_edbCityName.GetWindowText(strCityName);

	CString strCityRegion;
	m_edbCityRegion.GetWindowText(strCityRegion);

	m_recCityForInsertOrUpdate.nUpdateCounter = 0;
	wcscpy_s(m_recCityForInsertOrUpdate.szCityName, MAX_CITY_NAME, strCityName);
	wcscpy_s(m_recCityForInsertOrUpdate.szRegion, MAX_REGION_NAME, strCityRegion);

	EndDialog(IDOK);
}
void CDialogCities::OnClickedButtonCancel()
{
	EndDialog(IDCLOSE);
}

// Overrides
// ----------------
BOOL CDialogCities::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_edbCityName.SetLimitText(MAX_CITY_NAME - 1);
	m_edbCityRegion.SetLimitText(MAX_REGION_NAME - 1);

	switch (m_dialogMode)
	{
		case DialogModeView:
		{
			m_edbCityName.SetReadOnly(true);
			m_edbCityRegion.SetReadOnly(true);

			m_edbCityName.SetWindowTextW(CString(m_recCityForView.szCityName));
			m_edbCityRegion.SetWindowTextW(CString(m_recCityForView.szRegion));

			m_btnConfirm.EnableWindow(false);
		}
		break;

		case DialogModeEdit:
		{
			m_edbCityName.SetReadOnly(false);
			m_edbCityRegion.SetReadOnly(false);

			m_edbCityName.SetWindowTextW(CString(m_recCityForView.szCityName));
			m_edbCityRegion.SetWindowTextW(CString(m_recCityForView.szRegion));

			m_btnConfirm.EnableWindow(true);
		}
		break;

		default:
			return FALSE;
	}

	return TRUE;
}
void CDialogCities::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, BTN_CITIES_CANCEL, m_btnCancel);
	DDX_Control(pDX, BTN_CITIES_CONFIRM, m_btnConfirm);
	DDX_Control(pDX, STT_CITIES_NAME_EDIT_BOX, m_edbCityName);
	DDX_Control(pDX, STT_CITIES_REGION_EDIT_BOX, m_edbCityRegion);
}

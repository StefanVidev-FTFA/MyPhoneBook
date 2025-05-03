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
	CCommonListView::DialogMode dialogMod, CWnd* pParent)
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
	m_EditboxCityName.GetWindowText(strCityName);

	CString strCityRegion;
	m_EditboxCityRegion.GetWindowText(strCityRegion);

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

	m_EditboxCityName.SetLimitText(MAX_CITY_NAME);
	m_EditboxCityRegion.SetLimitText(MAX_REGION_NAME);

	switch (m_dialogMode)
	{
		case CCommonListView::DialogModeView:
		{
			m_EditboxCityName.SetReadOnly(true);
			m_EditboxCityRegion.SetReadOnly(true);

			m_EditboxCityName.SetWindowTextW(CString(m_recCityForView.szCityName));
			m_EditboxCityRegion.SetWindowTextW(CString(m_recCityForView.szRegion));

			m_BtnConfirm.EnableWindow(false);
		}
		break;

		case CCommonListView::DialogModeEdit:
		{
			m_EditboxCityName.SetReadOnly(false);
			m_EditboxCityRegion.SetReadOnly(false);

			m_EditboxCityName.SetWindowTextW(CString(m_recCityForView.szCityName));
			m_EditboxCityRegion.SetWindowTextW(CString(m_recCityForView.szRegion));

			m_BtnConfirm.EnableWindow(true);
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

	DDX_Control(pDX, BTN_CITIES_CANCEL, m_BtnCancel);
	DDX_Control(pDX, BTN_CITIES_CONFIRM, m_BtnConfirm);
	DDX_Control(pDX, STT_CITIES_NAME_EDIT_BOX, m_EditboxCityName);
	DDX_Control(pDX, STT_CITIES_REGION_EDIT_BOX, m_EditboxCityRegion);
}

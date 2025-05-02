#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogCities.h"

IMPLEMENT_DYNAMIC(CDialogCities, CDialogEx)

CDialogCities::CDialogCities(CITIES recCityForView,
	CCommonListView::DialogMode dialogMod, CWnd* pParent)
	: CDialogEx(IDD_CITIES, pParent), m_dialogMode(dialogMod), m_recCityForView(recCityForView)
{
}

CDialogCities::~CDialogCities()
{
}

BOOL CDialogCities::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_dialogMode == CCommonListView::DialogModeView)
	{
		 m_EditboxCityName.SetReadOnly(true);
		 m_EditboxCityRegion.SetReadOnly(true);

		 m_EditboxCityName.SetWindowTextW(CString(m_recCityForView.szCityName));
		 m_EditboxCityRegion.SetWindowTextW(CString(m_recCityForView.szRegion));

		 m_BtnConfirm.EnableWindow(false);
	}
	else
	{
		m_EditboxCityName.SetReadOnly(false);
		m_EditboxCityRegion.SetReadOnly(false);

		m_EditboxCityName.SetWindowTextW(CString(m_recCityForView.szCityName));
		m_EditboxCityRegion.SetWindowTextW(CString(m_recCityForView.szRegion));

		m_BtnConfirm.EnableWindow(true);
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


BEGIN_MESSAGE_MAP(CDialogCities, CDialogEx)
	ON_BN_CLICKED(BTN_CITIES_CONFIRM, &CDialogCities::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_CITIES_CANCEL, &CDialogCities::OnClickedButtonCancel)
END_MESSAGE_MAP()


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


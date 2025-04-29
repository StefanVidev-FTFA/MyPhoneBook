// CDialogCities.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CDialogCities.h"


// CDialogCities dialog

IMPLEMENT_DYNAMIC(CDialogCities, CDialogEx)

CDialogCities::CDialogCities(CWnd* pParent /*=nullptr*/,
	CCommonListView::DialogMode dialogMod, CITIES recCityForView)
	: CDialogEx(IDD_DIALOG7, pParent), m_dialogMode(dialogMod), m_recCityForView(recCityForView)
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
		m_EditBoxPhoneTypesField.SetReadOnly(true);
		m_EditBoxPhoneTypesField.SetWindowTextW(m_strPhoneType);
		m_ButtonPtsConfirm.EnableWindow(false);
	}
	else
	{
		m_EditBoxPhoneTypesField.SetReadOnly(false);
		m_ButtonPtsConfirm.EnableWindow(true);
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
END_MESSAGE_MAP()


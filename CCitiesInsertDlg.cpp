// CCitiesInsertDlg.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CCitiesInsertDlg.h"
#include "CitiesData.h"


// CCitiesInsertDlg dialog

IMPLEMENT_DYNAMIC(CCitiesInsertDlg, CDialogEx)

CCitiesInsertDlg::CCitiesInsertDlg(CWnd* pParent)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

// Constructor with data
//CCitiesInsertDlg::CCitiesInsertDlg(CWnd* pParent, CCitiesData& oCitiesData)
//	: CDialogEx(IDD_DIALOG1, pParent), m_oCitiesData(oCitiesData)
//{
//
//}

CCitiesInsertDlg::~CCitiesInsertDlg()
{
}

void CCitiesInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditBoxCity);
	DDX_Control(pDX, IDC_EDIT2, m_EditBoxRegion);
}


BEGIN_MESSAGE_MAP(CCitiesInsertDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCitiesInsertDlg::OnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON2, &CCitiesInsertDlg::OnClickedButtonCancel)
END_MESSAGE_MAP()


// CCitiesInsertDlg message handlers

void CCitiesInsertDlg::OnClickedButtonInsert()
{
	CString strCityName;
	m_EditBoxCity.GetWindowText(strCityName);


	CString strCityRegion;
	m_EditBoxRegion.GetWindowText(strCityRegion);




	AfxMessageBox(strCityName);
	AfxMessageBox(strCityRegion);


	CCitiesData oCitiesData;



	CITIES recCityForInsert;
	recCityForInsert.nUpdateCounter = 0;
	strncpy_s(recCityForInsert.szCityName, "temp example 1 city", MAX_CITY_NAME);
	strncpy_s(recCityForInsert.szRegion, "temp example 1 region", MAX_REGION_NAME);
	oCitiesData.Insert(recCityForInsert);

	AfxMessageBox(_T("SUCCESS???"));


}

void CCitiesInsertDlg::OnClickedButtonCancel()
{
	AfxMessageBox(_T("Cancel button clicked!"));
}

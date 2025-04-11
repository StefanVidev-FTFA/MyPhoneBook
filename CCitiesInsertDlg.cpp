// CCitiesInsertDlg.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CCitiesInsertDlg.h"
#include "CitiesData.h"


// CCitiesInsertDlg dialog

IMPLEMENT_DYNAMIC(CCitiesInsertDlg, CDialogEx)

CCitiesInsertDlg::CCitiesInsertDlg(CWnd* pParent /*= nullptr*/,CCitiesData* oCitiesData)
	: CDialogEx(IDD_DIALOG1, pParent), m_oCitiesData(oCitiesData)
{
}



//CCitiesInsertDlg::CCitiesInsertDlg(CCitiesData* oCitiesData)
//	: m_oCitiesData(oCitiesData)
//{
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

	CString strCityRegion;
	m_EditBoxRegion.GetWindowText(strCityRegion);



	CString strCityName;
	m_EditBoxCity.GetWindowText(strCityName);


	CW2A cityName(strCityName);
	CW2A cityRegion(strCityRegion);

	CITIES recCityForInsert;
	recCityForInsert.nUpdateCounter = 0;
	strcpy_s(recCityForInsert.szCityName, MAX_CITY_NAME, cityName);
	strcpy_s(recCityForInsert.szRegion, MAX_REGION_NAME, cityRegion);



	CCitiesData oCitiesData;
	oCitiesData.Insert(recCityForInsert);

	AfxMessageBox(_T("SUCCESS???"));


}

void CCitiesInsertDlg::OnClickedButtonCancel()
{
	AfxMessageBox(_T("Cancel button clicked!"));
}

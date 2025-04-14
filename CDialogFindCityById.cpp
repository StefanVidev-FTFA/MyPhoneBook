// CDialogFindCityById.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CDialogFindCityById.h"


// CDialogFindCityById dialog

IMPLEMENT_DYNAMIC(CDialogFindCityById, CDialogEx)

CDialogFindCityById::CDialogFindCityById(CWnd* pParent /*=nullptr*/,int mode)
	: CDialogEx(IDD_DIALOG2, pParent),m_nMode(mode)
{

}



BOOL CDialogFindCityById::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Safe to access controls here
	if (m_nMode == 2)
	{
		m_FindCityHeader.SetWindowText(_T("Please input ID of city you wish to Find."));
	}
	else if (m_nMode == 4) 
	{
		m_FindCityHeader.SetWindowText(_T("Please input ID of city you widh to Update."));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}




CDialogFindCityById::~CDialogFindCityById()
{
}

void CDialogFindCityById::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_FindByIdEditField);
	DDX_Control(pDX, STT_FIND_DIALOG_HEADER, m_FindCityHeader);
}


BEGIN_MESSAGE_MAP(CDialogFindCityById, CDialogEx)
	ON_BN_CLICKED(IDCANCEL2, &CDialogFindCityById::OnClickedFindByIdCancel)
	ON_BN_CLICKED(IDCANCEL, &CDialogFindCityById::OnBnClickedFindByIdFind)
END_MESSAGE_MAP()


// CDialogFindCityById message handlers


void CDialogFindCityById::OnBnClickedFindByIdFind()
{
	CString strTargetId;
	m_FindByIdEditField.GetWindowText(strTargetId);



	m_nIdToBeSelected = _ttoi(strTargetId);


	EndDialog(IDOK);
}

void CDialogFindCityById::OnClickedFindByIdCancel()
{
	EndDialog(IDOK);
}

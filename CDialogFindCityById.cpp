#pragma once
#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CDialogFindCityById.h"
#include "CommonMethods.h"


IMPLEMENT_DYNAMIC(CDialogFindCityById, CDialogEx)

CDialogFindCityById::CDialogFindCityById(CWnd* pParent /*=nullptr*/,CString strTableName)
	: CDialogEx(IDD_DIALOG2, pParent),m_strTableName(strTableName)
{
}

BOOL CDialogFindCityById::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString message = Utils::QueryWithStr(_T("Find a %s by ID"), m_strTableName);

	m_FindCityHeader.SetWindowText(message);

	return TRUE;
}

CDialogFindCityById::~CDialogFindCityById(){}

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

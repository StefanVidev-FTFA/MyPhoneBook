#pragma once
#include "afxdialogex.h"
#include "CitiesView.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesInsertDlg


/// <summary> ���� ������ �� ������� ����� ����������� ��� ������� �� ���� /// </summary>
class CDialogFindCityById : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogFindCityById)

	// Constructor / Destructor
	// ----------------
public:
	CDialogFindCityById(CWnd* pParent = nullptr);   
	virtual ~CDialogFindCityById();

	// Methods
	// ----------------
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedFindByIdCancel();
	afx_msg void OnBnClickedFindByIdFind();

	// Overrides
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	// Members
	// ----------------
public:
	int m_nIdToBeSelected = -1;
	CEdit m_FindByIdEditField;
	CStatic m_FindCityHeader;
};

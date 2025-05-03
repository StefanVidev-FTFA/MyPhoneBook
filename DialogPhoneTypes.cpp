#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "DialogPhoneTypes.h"
#include "Macros.h"

// Defines
// ----------------
IMPLEMENT_DYNAMIC(CDialogPhoneTypes, CDialogEx)
BEGIN_MESSAGE_MAP(CDialogPhoneTypes, CDialogEx)
	ON_BN_CLICKED(BTN_PTS_CONFIRM, &CDialogPhoneTypes::OnClickedButtonConfirm)
	ON_BN_CLICKED(BTN_PTS_CANCEL, &CDialogPhoneTypes::OnClickedButtonCancel)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CDialogPhoneTypes::CDialogPhoneTypes(CWnd* pParent /*=nullptr*/, CCommonListView::DialogMode dialogMod,CString strPhoneType)
	: CDialogEx(IDD_DIALOG7, pParent),m_dialogMode(dialogMod),m_strPhoneType(strPhoneType)
{
}
CDialogPhoneTypes::~CDialogPhoneTypes()
{
}

// Methods
// ----------------
void CDialogPhoneTypes::OnClickedButtonConfirm()
{
	CString strPhoneType;
	m_EditBoxPhoneTypesField.GetWindowText(strPhoneType);

	m_recPhoneTypeForUpdOrIns.nUpdateCounter = 0;
	wcscpy_s(m_recPhoneTypeForUpdOrIns.szPhoneType, strPhoneType);

	EndDialog(IDOK);
}
void CDialogPhoneTypes::OnClickedButtonCancel()
{
	EndDialog(IDOK);
}

// Overrides
// ----------------
void CDialogPhoneTypes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_PTS_PHONE_TYPE_BOX, m_EditBoxPhoneTypesField);
	DDX_Control(pDX, BTN_PTS_CONFIRM, m_ButtonPtsConfirm);
}
BOOL CDialogPhoneTypes::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_EditBoxPhoneTypesField.SetLimitText(MAX_PHONE_TYPE - 1);

	if (m_dialogMode == CCommonListView::DialogModeView)
	{
		m_EditBoxPhoneTypesField.SetReadOnly(true);
		m_EditBoxPhoneTypesField.SetWindowTextW(m_strPhoneType);

		m_ButtonPtsConfirm.EnableWindow(false);
	}
	else
	{
		m_EditBoxPhoneTypesField.SetReadOnly(false);
		m_EditBoxPhoneTypesField.SetWindowTextW(m_strPhoneType);

		m_ButtonPtsConfirm.EnableWindow(true);
	}

	return TRUE;
}

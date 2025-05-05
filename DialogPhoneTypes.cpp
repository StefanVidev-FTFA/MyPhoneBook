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
CDialogPhoneTypes::CDialogPhoneTypes( CCommonListView::DialogMode dialogMod
	,CString strPhoneType,
	CWnd* pParent
)
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
	m_edbPhoneTypesField.GetWindowText(strPhoneType);

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
	DDX_Control(pDX, STT_PTS_PHONE_TYPE_BOX, m_edbPhoneTypesField);
	DDX_Control(pDX, BTN_PTS_CONFIRM, m_btnPtsConfirm);
}
BOOL CDialogPhoneTypes::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_edbPhoneTypesField.SetLimitText(MAX_PHONE_TYPE - 1);

	if (m_dialogMode == CCommonListView::DialogModeView)
	{
		m_edbPhoneTypesField.SetReadOnly(true);
		m_edbPhoneTypesField.SetWindowTextW(m_strPhoneType);

		m_btnPtsConfirm.EnableWindow(false);
	}
	else
	{
		m_edbPhoneTypesField.SetReadOnly(false);
		m_edbPhoneTypesField.SetWindowTextW(m_strPhoneType);

		m_btnPtsConfirm.EnableWindow(true);
	}

	return TRUE;
}

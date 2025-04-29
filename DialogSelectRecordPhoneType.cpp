#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "resource.h"
#include "DialogSelectRecordPhoneType.h"


IMPLEMENT_DYNAMIC(DialogSelectRecordPhoneType, CDialogEx)

DialogSelectRecordPhoneType::DialogSelectRecordPhoneType(CWnd* pParent /*=nullptr*/, CString strPhoneType)
	: CDialogEx(IDD_SELECT_PHONE_TYPE, pParent), m_strPhoneType(strPhoneType)
{

}

DialogSelectRecordPhoneType::~DialogSelectRecordPhoneType()
{
}

BOOL DialogSelectRecordPhoneType::OnInitDialog()
{
    CDialogEx::OnInitDialog();


    m_textSelectedPhoneType.SetWindowText(m_strPhoneType);

    return TRUE;
}

void DialogSelectRecordPhoneType::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STT_SELECTED_PHONE_TYPE, m_textSelectedPhoneType);
}


BEGIN_MESSAGE_MAP(DialogSelectRecordPhoneType, CDialogEx)
	ON_BN_CLICKED(BTN_PTS_SELECTED_CLOSE, &DialogSelectRecordPhoneType::OnClickedButtonClose)
END_MESSAGE_MAP()


void DialogSelectRecordPhoneType::OnClickedButtonClose()
{
	EndDialog(IDOK);
}

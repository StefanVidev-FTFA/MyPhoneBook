#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PhoneBook.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "CitiesDoc.h"
#include "PhoneNumbersDoc.h"
#include "CitiesView.h"
#include "PhoneNumbersView.h"
#include "PersonsView.h"
#include "PersonsDoc.h"
#include "PhoneTypesView.h"
#include "PhoneTypesDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "DatabaseConnection.h"
#include "Macros.h"

BEGIN_MESSAGE_MAP(CPhoneBookApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPhoneBookApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

CPhoneBookApp::CPhoneBookApp() noexcept
{
	m_bHiColorIcons = TRUE;
	SetAppID(_T("PhoneBook.AppID.NoVersion"));
}

CPhoneBookApp theApp;

BOOL CPhoneBookApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;

	InitCommonControlsEx(&InitCtrls);
	CWinAppEx::InitInstance();

	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
	EnableTaskbarInteraction();
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);


	//----------------------------------------------------------

	CMultiDocTemplate* pDocTemplate3;
	pDocTemplate3 = new CMultiDocTemplate(IDR_PhoneBookPersons,
		RUNTIME_CLASS(CPersonsDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CPersonsView));

	if (!pDocTemplate3)
		return FALSE;
	AddDocTemplate(pDocTemplate3);


	CMultiDocTemplate* pDocTemplate1;
	pDocTemplate1 = new CMultiDocTemplate(IDR_PhoneBookCities,
		RUNTIME_CLASS(CCitiesDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CCitiesView));

	if (!pDocTemplate1)
		return FALSE;
	AddDocTemplate(pDocTemplate1);



	CMultiDocTemplate* pDocTemplate2;
	pDocTemplate2 = new CMultiDocTemplate(IDR_PhoneBookPhoneNumbers,
		RUNTIME_CLASS(CPhoneNumbersDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CPhoneNumbersView));

	if (!pDocTemplate2)
		return FALSE;
	AddDocTemplate(pDocTemplate2);


	CMultiDocTemplate* pDocTemplate4;
	pDocTemplate4 = new CMultiDocTemplate(IDR_PhoneBookPhoneTypes,
		RUNTIME_CLASS(CPhoneTypesDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CPhoneTypesView));

	if (!pDocTemplate4)
		return FALSE;
	AddDocTemplate(pDocTemplate4);
	//----------------------------------------------------------
	CDatabaseConnection::GetInstance().Connect();








	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CPhoneBookApp::ExitInstance()
{
	CDatabaseConnection::GetInstance().Disconnect();
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditSelectbyid();
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX){}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CPhoneBookApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
void CPhoneBookApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CPhoneBookApp::LoadCustomState(){}

void CPhoneBookApp::SaveCustomState(){}

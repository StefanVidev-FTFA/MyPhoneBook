
// PhoneBook.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PhoneBook.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "CitiesDoc.h"
#include "CitiesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CitiesTable.h"
#include "DatabaseConnection.h"

// CPhoneBookApp

BEGIN_MESSAGE_MAP(CPhoneBookApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPhoneBookApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CPhoneBookApp construction

CPhoneBookApp::CPhoneBookApp() noexcept
{
	m_bHiColorIcons = TRUE;


	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("PhoneBook.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CPhoneBookApp object

CPhoneBookApp theApp;


// CPhoneBookApp initialization

BOOL CPhoneBookApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_PhoneBookTYPE,
		RUNTIME_CLASS(CCitiesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCitiesView));


	CDatabaseConnection::GetInstance().Connect();

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
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
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();



	//CDatabaseConnection::GetInstance().Connect();
	

	CCitiesTable oCitiesTable;

	//CCitiesArray oCitiesArray;
	//oCitiesTable.SelectAll(oCitiesArray);
	//
	// 
	CITIES recCity;
	//oCitiesTable.SelectWhereID(1,recCity);
	// 
	// 
	//oCitiesTable.UpdateWhereID(4, recCity);
	// 
	// 
	//CITIES recCityForInsert;
	//recCityForInsert.nId = 1;
	//recCityForInsert.nUpdateCounter = 0;
	//strncpy_s(recCityForInsert.szCityName, "Targovishte_4", MAX_CITY_NAME - 1);
	//strncpy_s(recCityForInsert.szRegion, "Targovishte_4 -region", MAX_REGION_NAME - 1);
	//oCitiesTable.Insert(recCityForInsert);


	//oCitiesTable.DeleteWhereID(1020);



	return TRUE;
}

int CPhoneBookApp::ExitInstance()
{
	CDatabaseConnection::GetInstance().Disconnect();
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CPhoneBookApp message handlers


// CAboutDlg dialog used for App About

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

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CPhoneBookApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPhoneBookApp customization load/save methods

void CPhoneBookApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CPhoneBookApp::LoadCustomState()
{
}

void CPhoneBookApp::SaveCustomState()
{
}

// CPhoneBookApp message handlers




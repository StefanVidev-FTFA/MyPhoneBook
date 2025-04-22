#include "pch.h"
#include "framework.h"
#include "PhoneNumbersDoc.h"
#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Macros.h"
#include "PersonsData.h"

IMPLEMENT_DYNCREATE(CPhoneNumbersDoc, CDocument)
BEGIN_MESSAGE_MAP(CPhoneNumbersDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneNumbersDoc::CPhoneNumbersDoc() noexcept
{
	m_oCitiesData = new CCitiesData();
}
CPhoneNumbersDoc::~CPhoneNumbersDoc()
{
	delete m_oCitiesData;
	m_oCitiesData = nullptr;
}


// Methods
// ----------------
BOOL CPhoneNumbersDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPersonsData data;


	if (!data.SelectAll(m_oInitialPhoneNumbersArray))
	{
		MESSAGE_ERROR(_T("Failed to loadup the data for cities from database"));
		return FALSE;
	}

	return TRUE;
}

void CPhoneNumbersDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef _DEBUG
void CPhoneNumbersDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhoneNumbersDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

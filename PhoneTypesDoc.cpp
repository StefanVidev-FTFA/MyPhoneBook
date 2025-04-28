#include "pch.h"
#include "framework.h"
#include "PhoneTypesDoc.h"
#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Macros.h"
#include "PersonsData.h"

IMPLEMENT_DYNCREATE(CPhoneTypesDoc, CDocument)
BEGIN_MESSAGE_MAP(CPhoneTypesDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneTypesDoc::CPhoneTypesDoc() noexcept
{
}
CPhoneTypesDoc::~CPhoneTypesDoc()
{
}


// Methods
// ----------------
BOOL CPhoneTypesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPersonsData data;

	//if (!data.SelectAll(m_oInitialPhoneTypesArray))
	//{
	//	MESSAGE_ERROR(_T("Failed to loadup the data for phone types from database"));
	//	return FALSE;
	//}

	return TRUE;
}

void CPhoneTypesDoc::Serialize(CArchive& ar)
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
void CPhoneTypesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhoneTypesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

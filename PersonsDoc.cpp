#include "pch.h"
#include "framework.h"
#include "PersonsDoc.h"
#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Macros.h"
#include "PersonsData.h"

IMPLEMENT_DYNCREATE(CPersonsDoc, CDocument)
BEGIN_MESSAGE_MAP(CPersonsDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsDoc::CPersonsDoc() noexcept
{
}
CPersonsDoc::~CPersonsDoc()
{
}


// Methods
// ----------------
BOOL CPersonsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPersonsData data;

	if (!data.SelectAll(m_oInitialPersonsArray))
	{
		MESSAGE_ERROR(_T("Failed to loadup the data for persons from database"));
		return FALSE;
	}

	return TRUE;
}

void CPersonsDoc::Serialize(CArchive& ar)
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
void CPersonsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersonsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

#include "pch.h"
#include "framework.h"
#include "CitiesDoc.h"
#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CitiesArray.h"
#include "Macros.h"
#include "CitiesView.h"
#include "CitiesHint.h"
#include "PersonsData.h"
#include "GeneralHint.h"

IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)
BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)
END_MESSAGE_MAP()

	// Constructor / Destructor
	// ----------------
CCitiesDoc::CCitiesDoc() noexcept
{
}
CCitiesDoc::~CCitiesDoc()
{
}

	// Methods
	// ----------------
BOOL CCitiesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPersonsData personsData;

	if (!personsData.SelectAll(m_oInitialCitiesArray))
	{
		MESSAGE_ERROR(_T("Failed to loadup the data for cities from database"));
		return FALSE;
	}

	return TRUE;
}

bool CCitiesDoc::DatabaseUpdate(const int nId,const CITIES& recCity)
{
	//CCitiesData oCitiesData;
	//m_oCitiesData->UpdateWhereID(nId, recCity);

	CCitiesHint* pHint = new CCitiesHint(nId, recCity);
	UpdateAllViews(nullptr, CCitiesView::SqlOperationUpdateById, pHint);

	return true;
}
void CCitiesDoc::Serialize(CArchive& ar)
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
void CCitiesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCitiesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

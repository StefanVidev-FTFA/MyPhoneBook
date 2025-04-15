#include "pch.h"
#include "framework.h"
#include "CitiesDoc.h"
#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CitiesArray.h"
#include "CitiesData.h"
#include "Macros.h"
#include "CitiesView.h"
#include "CitiesHint.h"

IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)
BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)
END_MESSAGE_MAP()

	// Constructor / Destructor
	// ----------------
CCitiesDoc::CCitiesDoc() noexcept
{
	m_oCitiesData = new CCitiesData();
}
CCitiesDoc::~CCitiesDoc()
{
	delete m_oCitiesData;
	m_oCitiesData = nullptr;
}



	// Methods
	// ----------------
BOOL CCitiesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (!m_oCitiesData->SelectAll(m_oInitialCitiesArray))
	{
		MESSAGE_ERROR(_T("Failed to loadup the data for cities from database"));

		return FALSE;
	}

	return TRUE;
}

bool CCitiesDoc::DatabaseUpdate(const int nId,const CITIES& recCity)
{
	CCitiesData oCitiesData;
	m_oCitiesData->UpdateWhereID(nId, recCity);

	CCitiesHint* pHint = new CCitiesHint(nId, recCity);
	UpdateAllViews(nullptr, CCitiesView::SqlOperationUpdateById, pHint);

	return true;
}

bool CCitiesDoc::DatabaseSelectAll()
{
	CCitiesArray *pCitiesArray = new CCitiesArray();
	m_oCitiesData->SelectAll(*pCitiesArray);

	UpdateAllViews(nullptr, CCitiesView::SqlOperationSelectAll, pCitiesArray);
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

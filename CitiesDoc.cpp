#include "pch.h"
#include "framework.h"
#include "CitiesDoc.h"
#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Macros.h"
#include "CitiesView.h"
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
bool CCitiesDoc::DatabaseUpdate(const CITIES& recItem)
{
	CCitiesTable oCitiesTable;
	if (!oCitiesTable.UpdateById(recItem.nId, recItem))
	{
		MESSAGE_ERROR(_T("Failed to update the city with ID %d"), nId);
		return false;
	}

	CGeneralHint<CITIES>* pHint = new CGeneralHint<CITIES>(recItem);
	UpdateAllViews(nullptr, CCommonListView::SqlOperationUpdateById, pHint);

	delete pHint;

	return true;
}

bool CCitiesDoc::DatabaseDelete(const int nId)
{
	CCitiesTable oCitiesTable;
	if (oCitiesTable.DeleteWhereId(nId))
	{
		UpdateAllViews(nullptr, CCommonListView::SqlOperationDelete, nullptr);
		return true;
	}
	else
	{
		return false;
	}

	// bez else
	return true;
}

bool CCitiesDoc::DatabaseInsert(CITIES& recItem)
{
	CCitiesTable oCitiesTable;
	if (oCitiesTable.Insert(recItem))
	{
		CGeneralHint<CITIES>* newHint = new CGeneralHint<CITIES>(recItem);

		UpdateAllViews(nullptr, CCommonListView::SqlOperationInsert, newHint);
		return true;
	}
	else
	{
		return false;
	}

	// bez else
	return true;
}

bool CCitiesDoc::DatabaseSelectAll()
{
	CCitiesTable oCitiesTable;
	CSmartArray<CITIES>* pItemsArray = new CSmartArray<CITIES>();

	oCitiesTable.SelectAll(*pItemsArray);

	UpdateAllViews(nullptr, CCommonListView::SqlOperationSelectAll, pItemsArray);

	delete pItemsArray;

	return true;
}

bool CCitiesDoc::DatabaseSelectById(const long nId)
{
	CCitiesTable oCitiesTable;
	CITIES recFoundItem;

	oCitiesTable.SelectWhereID(nId, recFoundItem);

	CGeneralHint<CITIES> oHint(recFoundItem);
	UpdateAllViews(nullptr, CCommonListView::SqlOperationSelectById, &oHint);

	return true;
}


	// Methods
	// ----------------
BOOL CCitiesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CCitiesTable oCitiesTable;
	if (!oCitiesTable.SelectAll(m_oInitialCitiesArray))
	{
		MESSAGE_ERROR(_T("Failed to loadup the data for cities from database"));
		return FALSE;
	}

	return TRUE;
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

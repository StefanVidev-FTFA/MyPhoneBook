#include "pch.h"
#include "framework.h"
#include "PersonsDoc.h"
#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Macros.h"
#include "PersonsData.h"
#include "CommonListView.h"

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

	CPersonsTable oPersonsTable;

	if (!oPersonsTable.SelectAll(m_oInitialPersonsArray))
	{
		MESSAGE_ERROR(_T("Failed to loadup the data for persons from database"));
		return FALSE;
	}

	return TRUE;
}

bool CPersonsDoc::DatabaseSelectAll()
{
	CPersonsTable oPersonsTable;
	CSmartArray<PERSONS>* pItemsArray = new CSmartArray<PERSONS>();

	oPersonsTable.SelectAll(*pItemsArray);

	UpdateAllViews(nullptr, CCommonListView::SqlOperationSelectAll, pItemsArray);

	return true;
}

bool CPersonsDoc::DatabaseInsert(PERSONS& recItem,const CSmartArray<PHONE_NUMBERS>& phoneNumbers)
{
	CPersonsData oData;

	if (oData.CommitNewPerson(recItem, phoneNumbers))
	{
		CGeneralHint<PERSONS>* newHint = new CGeneralHint<PERSONS>(recItem);

		UpdateAllViews(nullptr, CCommonListView::SqlOperationInsert, newHint);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

bool CPersonsDoc::DatabaseDelete(const int nId)
{
	CPersonsTable oPersonsTable;

	if (oPersonsTable.DeleteWhereId(nId))
	{
		UpdateAllViews(nullptr, CCommonListView::SqlOperationDelete, nullptr);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

bool CPersonsDoc::DatabaseUpdate(const PERSONS& recItem)
{
	CPersonsTable oPersonsTable;

	if (oPersonsTable.UpdateById(recItem.nId, recItem))
	{
		CGeneralHint<PERSONS>* pHint = new CGeneralHint<PERSONS>(recItem);
		UpdateAllViews(nullptr, CCommonListView::SqlOperationUpdateById, pHint);
	}
	else
	{
		MESSAGE_ERROR(_T("Failed to update the person with ID %d"), nId);
		return false;
	}

	return true;
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

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

// Defines
// ----------------
IMPLEMENT_DYNCREATE(CPersonsDoc, CDocument)
BEGIN_MESSAGE_MAP(CPersonsDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsDoc::CPersonsDoc() noexcept
{
	CCitiesTable oCitiesTable;
	oCitiesTable.SelectAll(m_oCitiesArray); // във функция 
}
CPersonsDoc::~CPersonsDoc()
{
}

// Methods
// ----------------
bool CPersonsDoc::DatabaseSelectAll()
{
	CPersonsTable oPersonsTable;
	CSmartArray<PERSONS>* pItemsArray = new CSmartArray<PERSONS>();

	oPersonsTable.SelectAll(*pItemsArray);

	UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesSelectAll, pItemsArray);

	return true;
}
bool CPersonsDoc::DatabaseInsert(PERSONS& recItem,const CSmartArray<PHONE_NUMBERS>& phoneNumbers)
{
	CPersonsData oData;

	if (oData.AddPerson(recItem, phoneNumbers))
	{
		CGeneralHint<PERSONS>* newHint = new CGeneralHint<PERSONS>(recItem);

		UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesInsert, newHint);
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

	if (!oPersonsTable.DeleteWhereId(nId)) 
	{
		MESSAGE_ERROR(_T("Failed to delete the person with ID %d"), nId);
		return false;
	}

	UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesDelete, nullptr);

	return true;
}
bool CPersonsDoc::DatabaseUpdate(const PERSONS& recPerson,CSmartArray<PHONE_NUMBERS>& phoneNumbers)
{
	CPersonsData oPersonsData;

	if (!oPersonsData.UpdatePerson(recPerson, phoneNumbers))
	{
		MESSAGE_ERROR(_T("Failed to update the person with ID %d"), nId);
		return false;
	}

	CGeneralHint<PERSONS>* pHint = new CGeneralHint<PERSONS>(recPerson);
	UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesUpdateById, pHint);

	delete pHint;

	return true;
}
bool CPersonsDoc::DatabaseSelectById(const long nId, PERSONS& recPerson)
{
	CPersonsData pPersonsData;

	if (!pPersonsData.SelectWhereID(nId, recPerson))
	{
		MESSAGE_ERROR(_T("Failed to load the person with ID %d"), nId);
		return false;
	}

	return true;
}
// Overrides
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

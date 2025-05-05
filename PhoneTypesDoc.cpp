#include "pch.h"
#include "framework.h"
#include "PhoneTypesDoc.h"
#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Macros.h"
#include "PersonsData.h"
#include "GeneralHint.h"
#include "CommonListView.h"

// Defines
// ----------------
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
bool CPhoneTypesDoc::DatabaseUpdate(const PHONE_TYPES& recItem)
{
	CPhoneTypesTable oPhoneTypesTable;

	if (oPhoneTypesTable.UpdateById(recItem.nId, recItem))
	{
		CGeneralHint<PHONE_TYPES>* pHint = new CGeneralHint<PHONE_TYPES>(recItem);
		UpdateAllViews(nullptr, CCommonListView::SqlOperationUpdateById, pHint);
	}
	else
	{
		MESSAGE_ERROR(_T("Failed to update the phone type with ID %d"), nId);
		return false;
	}

	return true;
}
bool CPhoneTypesDoc::DatabaseDelete(const int nId)
{
	CPhoneTypesTable oPhoneTypesTable;

	if (oPhoneTypesTable.DeleteWhereId(nId))
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
bool CPhoneTypesDoc::DatabaseInsert(PHONE_TYPES& recItem)
{
	CPhoneTypesTable oPhoneTypesTable;

	if (oPhoneTypesTable.Insert(recItem))
	{
		CGeneralHint<PHONE_TYPES>* newHint = new CGeneralHint<PHONE_TYPES>(recItem);

		UpdateAllViews(nullptr, CCommonListView::SqlOperationInsert, newHint);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}
bool CPhoneTypesDoc::DatabaseSelectAll()
{
	CPhoneTypesTable oPhoneTypesTable;
	CSmartArray<PHONE_TYPES>* pItemsArray = new CSmartArray<PHONE_TYPES>();

	oPhoneTypesTable.SelectAll(*pItemsArray);

	UpdateAllViews(nullptr, CCommonListView::SqlOperationSelectAll, pItemsArray);

	return true;
}
bool CPhoneTypesDoc::DatabaseSelectById(const long nId,PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypesTable;

	if(!oPhoneTypesTable.SelectWhereID(nId, recPhoneType))
	{
		MESSAGE_ERROR(_T("Failed to select the phone type with ID %d"), nId);
		return false;
	}

	return true;
}

// Overrides
// ----------------
BOOL CPhoneTypesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPhoneTypesTable oData;

	if (!oData.SelectAll(m_oInitialPhoneTypesArray))
	{
		MESSAGE_ERROR(_T("Failed to loadup the data for phone types from database"));
		return FALSE;
	}

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

#include "pch.h"
#include "framework.h"
#include "PhoneNumbersDoc.h"
#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Macros.h"
#include "PersonsData.h"
#include "CommonListView.h"

IMPLEMENT_DYNCREATE(CPhoneNumbersDoc, CDocument)
BEGIN_MESSAGE_MAP(CPhoneNumbersDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneNumbersDoc::CPhoneNumbersDoc() noexcept
{
}
CPhoneNumbersDoc::~CPhoneNumbersDoc()
{
}

bool CPhoneNumbersDoc::DatabaseUpdate(const PHONE_NUMBERS& recItem)
{
	CPhoneNumbersTable oPhoneNumbersTable;
	if (oPhoneNumbersTable.UpdateById(recItem.nId, recItem))
	{
		CGeneralHint<PHONE_NUMBERS>* pHint = new CGeneralHint<PHONE_NUMBERS>(recItem);
		UpdateAllViews(nullptr, CCommonListView::SqlOperationUpdateById, pHint);
	}
	else
	{
		MESSAGE_ERROR(_T("Failed to update the city with ID %d"), nId);
		return false;
	}

	return true;
}

bool CPhoneNumbersDoc::DatabaseDelete(const int nId)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	if (oPhoneNumbersTable.DeleteWhereId(nId))
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

bool CPhoneNumbersDoc::DatabaseInsert(PHONE_NUMBERS& recItem)
{
	CPhoneNumbersTable oPhoneNumbersTable;
	if (oPhoneNumbersTable.Insert(recItem))
	{
		CGeneralHint<PHONE_NUMBERS>* newHint = new CGeneralHint<PHONE_NUMBERS>(recItem);

		UpdateAllViews(nullptr, CCommonListView::SqlOperationInsert, newHint);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

bool CPhoneNumbersDoc::DatabaseSelectAll()
{
	CPhoneNumbersTable oPhoneNumbersTable;
	CSmartArray<PHONE_NUMBERS>* pItemsArray = new CSmartArray<PHONE_NUMBERS>();

	oPhoneNumbersTable.SelectAll(*pItemsArray);

	UpdateAllViews(nullptr, CCommonListView::SqlOperationSelectAll, pItemsArray);

	return true;
}

bool CPhoneNumbersDoc::DatabaseSelectById(const long nId)
{
	CPhoneNumbersTable oPhoneNumbersTable;
	PHONE_NUMBERS recFoundItem;

	oPhoneNumbersTable.SelectWhereID(nId, recFoundItem);

	CGeneralHint<PHONE_NUMBERS>* pHint = new CGeneralHint<PHONE_NUMBERS>(recFoundItem);
	UpdateAllViews(nullptr, CCommonListView::SqlOperationSelectById, pHint);

	return true;
}
// Methods
// ----------------
BOOL CPhoneNumbersDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPhoneNumbersTable oPhoneNumbersTable;

	if (!oPhoneNumbersTable.SelectAll(m_oInitialPhoneNumbersArray))
	{
		MESSAGE_ERROR(_T("Failed to loadup the data for phone numbers from database"));
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

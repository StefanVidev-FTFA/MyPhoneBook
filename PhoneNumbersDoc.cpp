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

// Defines
// ----------------
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

// Methods
// ----------------
void CPhoneNumbersDoc::AssignPersonsMap(CMap<int, int, CString, const CString&>& personsMap)
{
	CSmartArray<PERSONS>* pPersonsArray = new CSmartArray<PERSONS>();
	CPersonsData oPersonData;
	oPersonData.SelectAll(*pPersonsArray);

	for (INT_PTR nIndex = 0; nIndex < pPersonsArray->GetSize(); nIndex++)
	{
		personsMap.SetAt(pPersonsArray->GetAt(nIndex)->nId, CString(pPersonsArray->GetAt(nIndex)->szFirstName));
	}
}
void CPhoneNumbersDoc::AssignPhoneTypesMap(CMap<int, int, CString, const CString&>& phoneTypesMap)
{
	CSmartArray<PHONE_TYPES>* pPhoneTypesArray = new CSmartArray<PHONE_TYPES>();
	CPhoneTypesTable pPhoneTypesTable;
	pPhoneTypesTable.SelectAll(*pPhoneTypesArray);

	for (INT_PTR nIndex = 0; nIndex < pPhoneTypesArray->GetSize(); nIndex++)
	{
		phoneTypesMap.SetAt(pPhoneTypesArray->GetAt(nIndex)->nId, CString(pPhoneTypesArray->GetAt(nIndex)->szPhoneType));
	}
}

bool CPhoneNumbersDoc::Update(const PHONE_NUMBERS& recItem)
{
	CPhoneNumbersTable oPhoneNumbersTable;
	if (oPhoneNumbersTable.UpdateById(recItem.nId, recItem))
	{
		CGeneralHint<PHONE_NUMBERS>* pHint = new CGeneralHint<PHONE_NUMBERS>(recItem);
		UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesUpdateById, pHint);
	}
	else
	{
		MESSAGE_ERROR(_T("Failed to update the city with ID %d"), nId);
		return false;
	}

	return true;
}
bool CPhoneNumbersDoc::Delete(const int nId)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	if (!oPhoneNumbersTable.DeleteWhereId(nId)) {
		MESSAGE_ERROR(_T("Failed to delete the phone number with ID %d"), nId);
		return false;
	}

	UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesDelete, nullptr);
	return true;
}
bool CPhoneNumbersDoc::Insert(PHONE_NUMBERS& recItem)
{
	CPhoneNumbersTable oPhoneNumbersTable;
	if (oPhoneNumbersTable.Insert(recItem))
	{
		CGeneralHint<PHONE_NUMBERS>* newHint = new CGeneralHint<PHONE_NUMBERS>(recItem);

		UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesInsert, newHint);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}
bool CPhoneNumbersDoc::SelectAll()
{
	CPhoneNumbersTable oPhoneNumbersTable;
	CSmartArray<PHONE_NUMBERS>* pItemsArray = new CSmartArray<PHONE_NUMBERS>();

	oPhoneNumbersTable.SelectAll(*pItemsArray);

	UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesSelectAll, pItemsArray);

	return true;
}
bool CPhoneNumbersDoc::SelectById(const long nId,PHONE_NUMBERS& recPhoneNumber)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	if(!oPhoneNumbersTable.SelectWhereID(nId, recPhoneNumber))
	{
		MESSAGE_ERROR(_T("Failed to load the phone number with ID %d"), nId);
		return false;
	}

	return true;
}

// Overrides
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

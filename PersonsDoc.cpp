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
	oCitiesTable.SelectAll(m_oCitiesArray); // ��� ������� 
}
CPersonsDoc::~CPersonsDoc()
{
}

// Methods
// ----------------
bool CPersonsDoc::SelectAll()
{
	CPersonsData oData;
	CSmartArray<PERSONS>* pItemsArray = new CSmartArray<PERSONS>();

	if (!oData.SelectAll(*pItemsArray))
	{
		return false;
	}

	UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesSelectAll, pItemsArray);

	return true;
}
bool CPersonsDoc::Insert(PERSONS& recItem,const CSmartArray<PHONE_NUMBERS>& phoneNumbers)
{
	CPersonsData oData;

	if (!oData.AddPerson(recItem, phoneNumbers))
	{
		CUtils::MessageWithInt(_T("Failed to add the person with ID %d"), recItem.nId);
		return false;
	}

	CGeneralHint<PERSONS>* newHint = new CGeneralHint<PERSONS>(recItem);
	UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesInsert, newHint);
	delete newHint;

	return true;
}
bool CPersonsDoc::Delete(const int nId)
{
	CPersonsData oPersonsData;

	if (!oPersonsData.DeletePerson(nId))
	{
		CUtils::MessageWithInt(_T("Failed to delete the person with ID %d"), nId);
		return false;
	}

	UpdateAllViews(nullptr, CCommonListView::ListViewHintTypesDelete, nullptr);

	return true;
}
bool CPersonsDoc::Update(const PERSONS& recPerson,CSmartArray<PHONE_NUMBERS>& phoneNumbers)
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
bool CPersonsDoc::SelectById(const long nId, PERSONS& recPerson)
{
	CPersonsData pPersonsData;

	if (!pPersonsData.SelectWhereID(nId, recPerson))
	{
		MESSAGE_ERROR(_T("Failed to load the person with ID %d"), nId);
		return false;
	}

	return true;
}
void CPersonsDoc::AssignCitiesMap(CMap<int, int, CString, const CString&>& citiesMap)
{
	CSmartArray<CITIES>* pCitiesArray = new CSmartArray<CITIES>();
	CCitiesTable oCitiesTable;

	if (!oCitiesTable.SelectAll(*pCitiesArray))
	{
		MESSAGE_ERROR(_T("Failed to select all cities"));
		return;
	}

	for (INT_PTR nIndex = 0; nIndex < pCitiesArray->GetSize(); nIndex++)
	{
		citiesMap.SetAt(pCitiesArray->GetAt(nIndex)->nId, CString(pCitiesArray->GetAt(nIndex)->szCityName));
	}
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

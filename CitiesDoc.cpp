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

	//CSmartArray<CITIES> citiesArray;
	//personsData.SelectAll(citiesArray);


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

bool CCitiesDoc::DatabaseSelectAll()
{
	CSmartArray<CITIES>* pCitiesArray = new CSmartArray<CITIES>();

	//m_oCitiesData->SelectAll(*pCitiesArray);

	UpdateAllViews(nullptr, CCitiesView::SqlOperationSelectAll, pCitiesArray);
	return true;
}

bool CCitiesDoc::DatabaseSelectById(const long nId)
{

	CITIES recFoundCity;

	//m_oCitiesData->SelectWhereID(nId, recFoundCity);

	CCitiesHint* pHint = new CCitiesHint(nId, recFoundCity);

	UpdateAllViews(nullptr, CCitiesView::SqlOperationSelectById, pHint);
	return true;
}
bool CCitiesDoc::DatabaseInsert(const CString& strCityName,const CString& strCityRegion)
{
	CITIES recCityForInsert;
	recCityForInsert.nUpdateCounter = 0;
	wcscpy_s(recCityForInsert.szCityName, MAX_CITY_NAME, strCityName);
	wcscpy_s(recCityForInsert.szRegion, MAX_REGION_NAME, strCityRegion);

	//CCitiesData oCitiesData;
	//if (oCitiesData.Insert(recCityForInsert))
	//{
	//	CCitiesHint* pHint = new CCitiesHint(recCityForInsert.nId, recCityForInsert);
	//	UpdateAllViews(nullptr, CCitiesView::SqlOperationInsert, pHint);
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	return true;
}

bool CCitiesDoc::DatabaseDelete(const int nId)
{
	//CCitiesData oCitiesData;

	//if (oCitiesData.DeleteWhereID(nId))
	//{

	//	UpdateAllViews(nullptr, CCitiesView::SqlOperationDelete, nullptr);
	//	return true;
	//}
	//else 
	//{
	//	return false;
	//}
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

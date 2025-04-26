#pragma once

#include "SmartArray.h"
#include "PersonsData.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CCommonDocument : public CDocument
{
protected:
    CCommonDocument() noexcept = default;

public:
    virtual ~CCommonDocument() = default;

	template<typename tableType>
	bool DatabaseSelectById(const long nId)
	{
		tableType recFoundItem;
		CPersonsData oData;

		oData.SelectById(nId, recFoundItem);

		CCitiesHint* pHint = new CCitiesHint(nId, recFoundItem);
		UpdateAllViews(nullptr, CCommonListView::SqlOperationSelectById, pHint);

		return true;
	}

	template<typename tableType>
	bool DatabaseSelectAll()
	{
		CSmartArray<tableType>* pItemsArray = new CSmartArray<tableType>();
		CPersonsData oData;

		oData.SelectAll(*pItemsArray);

		UpdateAllViews(nullptr, CCommonListView::SqlOperationSelectAll, pItemsArray);

		return true;
	}

	template<typename tableType>
	bool DatabaseInsert(tableType& recItem)
	{
		tableType recItemForInsert = recItem;

		CPersonsData oData;

		if (oData.Insert(recItemForInsert))
		{

			CGeneralHint<tableType>* newHint = new CGeneralHint<tableType>(recItemForInsert);

			UpdateAllViews(nullptr, CCommonListView::SqlOperationInsert, newHint);
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}

	template<typename tableType>
	bool DatabaseDelete(const int nId)
	{
		CPersonsData oData;

		if (oData.DeleteById<tableType>(nId))
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


};
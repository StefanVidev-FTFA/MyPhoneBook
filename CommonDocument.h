#pragma once

#include "SmartArray.h"
#include "PersonsData.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> ���� �� extend-���� �� �������� �� CDocument, � ��� ������ � ��������� �� ������ ����� </summary>
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


};
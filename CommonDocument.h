#pragma once

#include "SmartArray.h"
#include "PersonsData.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
template <typename tableType>
class CCommonDocument : public CDocument
{

	// Constructor / Destructor
	// ----------------
protected:
	CCommonDocument() noexcept;
	DECLARE_DYNCREATE(CCommonDocument)
public:
	virtual ~CCommonDocument();

	// Methods
	// ----------------
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);


	template <typename tableType>
	bool DatabaseSelectById(const long nId) 
	{
		tableType recFoundItem;
		CPersonsData oData;

		oData.SelectById(nId, recFoundItem);


		CCitiesHint* pHint = new CCitiesHint(nId, recFoundItem);

		UpdateAllViews(nullptr, CCitiesView::SqlOperationSelectById, pHint);
		return true;
	}


	// Overrides
	// ----------------
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	DECLARE_MESSAGE_MAP()

	//Members
public:
	CSmartArray<tableType> m_oInitialItemsArray;
};
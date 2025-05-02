#pragma once
#include "SmartArray.h"
#include "CommonDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData
/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CCitiesDoc : public CCommonDocument
{
// Defines
// ----------------
DECLARE_DYNCREATE(CCitiesDoc)
DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
protected:
	CCitiesDoc() noexcept;
public:
	virtual ~CCitiesDoc();

// Methods
// ----------------
public:
	bool DatabaseSelectById(const long nId);
	bool DatabaseSelectAll();
	bool DatabaseInsert(CITIES& recItem);
	bool DatabaseDelete(const int nId);
	bool DatabaseUpdate(const CITIES& recItem);

// Overrides
// ----------------
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Members
// ----------------
public:
	CSmartArray<CITIES> m_oInitialCitiesArray;
	int m_SelectByIdTarget = -1;
};
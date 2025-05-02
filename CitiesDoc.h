#pragma once
#include "SmartArray.h"
#include "CommonDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData
/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CCitiesDoc : public CCommonDocument
{
	// Constructor / Destructor
	// ----------------
protected:
	CCitiesDoc() noexcept;
	DECLARE_DYNCREATE(CCitiesDoc)
public:
	virtual ~CCitiesDoc();

	// Methods
	// ----------------
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	bool DatabaseSelectById(const long nId);
	bool DatabaseSelectAll();
	bool DatabaseInsert(CITIES& recItem);
	bool DatabaseDelete(const int nId);
	bool DatabaseUpdate(const CITIES& recItem);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()

	// Members
	// ----------------
public:
	CSmartArray<CITIES> m_oInitialCitiesArray;
	int m_SelectByIdTarget = -1;
};
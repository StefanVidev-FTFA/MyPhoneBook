#pragma once

#include "PhoneTypes.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData
/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CPhoneTypesDoc : public CDocument
{
// Defines
// ----------------
	DECLARE_DYNCREATE(CPhoneTypesDoc)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
protected:
	CPhoneTypesDoc() noexcept;
public:
	virtual ~CPhoneTypesDoc();

// Methods
// ----------------
public:
	bool DatabaseSelectById(const long nId);
	bool DatabaseSelectAll();
	bool DatabaseInsert(PHONE_TYPES& recItem);
	bool DatabaseDelete(const int nId);
	bool DatabaseUpdate(const PHONE_TYPES& recItem);

	// Overrides
	// ----------------
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Members
// ----------------
public:
	CSmartArray<PHONE_TYPES> m_oInitialPhoneTypesArray;
	int m_SelectByIdTarget = -1;
};

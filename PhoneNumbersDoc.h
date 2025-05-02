#pragma once
#include "PhoneNumbers.h"
#include "CommonDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CPhoneNumbersDoc : public CCommonDocument
{
// Defines
// ----------------
	DECLARE_DYNCREATE(CPhoneNumbersDoc)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
protected:
	CPhoneNumbersDoc() noexcept;
public:
	virtual ~CPhoneNumbersDoc();

	// Methods
	// ----------------
public:
	bool DatabaseSelectById(const long nId);
	bool DatabaseSelectAll();
	bool DatabaseInsert(PHONE_NUMBERS& recItem);
	bool DatabaseDelete(const int nId);
	bool DatabaseUpdate(const PHONE_NUMBERS& recItem);

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
	CSmartArray<PHONE_NUMBERS> m_oInitialPhoneNumbersArray;
	int m_SelectByIdTarget = -1;
};

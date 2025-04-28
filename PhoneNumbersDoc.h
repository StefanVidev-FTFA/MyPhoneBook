#pragma once
#include "PhoneNumbers.h"
#include "CommonDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CPhoneNumbersDoc : public CCommonDocument
{

	// Constructor / Destructor
	// ----------------
protected:
	CPhoneNumbersDoc() noexcept;
	DECLARE_DYNCREATE(CPhoneNumbersDoc)
public:
	virtual ~CPhoneNumbersDoc();

	// Methods
	// ----------------
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);


	// Overrides
	// ----------------
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Members
	// ----------------
public:
	CSmartArray<PHONE_NUMBERS> m_oInitialPhoneNumbersArray;
	int m_SelectByIdTarget = -1;


protected:
	DECLARE_MESSAGE_MAP()
public:
	bool DatabaseSelectById(const long nId);
	bool DatabaseSelectAll();
	bool DatabaseInsert(PHONE_NUMBERS& recItem);
	bool DatabaseDelete(const int nId);
	bool DatabaseUpdate(const PHONE_NUMBERS& recItem);

};
#pragma once
#include "Persons.h"
#include "PhoneNumbers.h"
#include "SmartArray.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDoc
/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CPersonsDoc : public CDocument
{
// Defines
// ----------------
	DECLARE_DYNCREATE(CPersonsDoc)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
protected:
	CPersonsDoc() noexcept;
public:
	virtual ~CPersonsDoc();

// Methods
// ----------------
public:
	bool DatabaseSelectById(const long nId);
	bool DatabaseSelectAll();
	bool DatabaseInsert(PERSONS& recItem, const CSmartArray<PHONE_NUMBERS>& phoneNumbers);
	bool DatabaseDelete(const int nId);
	bool DatabaseUpdate(const PERSONS& recItem,CSmartArray<PHONE_NUMBERS>& phoneNumbers);

// Overrides
// ----------------
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Members
// ----------------
public:
	CSmartArray<PERSONS> m_oInitialPersonsArray;
	int m_SelectByIdTarget = -1;

	CSmartArray<CITIES> m_oCitiesArray;	
};

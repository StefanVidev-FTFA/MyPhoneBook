#pragma once
#include "Persons.h"
#include "PhoneNumbers.h"
#include "SmartArray.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDoc
/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CPersonsDoc : public CDocument
{

	// Constructor / Destructor
	// ----------------
protected:
	CPersonsDoc() noexcept;
	DECLARE_DYNCREATE(CPersonsDoc)
public:
	virtual ~CPersonsDoc();

	// Methods
	// ----------------
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

	bool DatabaseSelectById(const long nId);
	bool DatabaseSelectAll();
	bool DatabaseInsert(PERSONS& recItem, const CSmartArray<PHONE_NUMBERS>& phoneNumbers);
	bool DatabaseDelete(const int nId);
	bool DatabaseUpdate(const PERSONS& recItem,CSmartArray<PHONE_NUMBERS>& phoneNumbers);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()

	// Members
	// ----------------
public:
	CSmartArray<PERSONS> m_oInitialPersonsArray;
	int m_SelectByIdTarget = -1;

	CSmartArray<CITIES> m_oCitiesArray;	
};

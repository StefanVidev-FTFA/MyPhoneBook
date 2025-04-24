#pragma once
#include "PhoneTypes.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CPhoneTypesDoc : public CDocument
{

	// Constructor / Destructor
	// ----------------
protected:
	CPhoneTypesDoc() noexcept;
	DECLARE_DYNCREATE(CPhoneTypesDoc)
public:
	virtual ~CPhoneTypesDoc();

	// Methods
	// ----------------
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

	///<summary >Избира всички градове от базата данни ///</summary>
	bool DatabaseSelectAll();
	// Overrides
	// ----------------
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Members
	// ----------------
public:
	CSmartArray<PHONE_TYPES> m_oInitialPhoneTypesArray;
	int m_SelectByIdTarget = -1;


protected:
	DECLARE_MESSAGE_MAP()

};
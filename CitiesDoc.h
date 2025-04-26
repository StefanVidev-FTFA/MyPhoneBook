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

	///<summary> Обновява информацията за град въвs базата данни ///</summary>
	bool DatabaseUpdate(const int nId, const CITIES& recCity);
	///<summary >Въвежда за град във базата данни ///</summary>
	bool DatabaseInsert(CITIES& recItem);
	///<summary >Трие град от базата данни ///</summary>
	bool DatabaseDelete(const int nId);


	// Overrides
	// ----------------
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Members
	// ----------------
public:
	CSmartArray<CITIES> m_oInitialCitiesArray;
	int m_SelectByIdTarget = -1;


protected:
	DECLARE_MESSAGE_MAP()

};
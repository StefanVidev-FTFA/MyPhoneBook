#pragma once
#include "CitiesData.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CCitiesDoc : public CDocument
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

	///<summary> Обновява информацията за град във базата данни ///</summary>
	bool DatabaseUpdate(const int nId, const CITIES& recCity);
	///<summary >Въвежда за град във базата данни ///</summary>
	bool DatabaseInsert(const CString& strCityName, const CString& strCityRegion);
	///<summary >Трие град от базата данни ///</summary>
	bool DatabaseDelete(const int nId);
	///<summary >Избира град от базата данни ///</summary>
	bool DatabaseSelectById(const long nId);
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
	CSmartArray<CITIES> m_oInitialCitiesArray;
	CCitiesData* m_oCitiesData;
	int m_SelectByIdTarget = -1;


protected:
	DECLARE_MESSAGE_MAP()

};
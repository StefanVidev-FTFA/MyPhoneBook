#pragma once
#include "CitiesData.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> ���� �� extend-���� �� �������� �� CDocument, � ��� ������ � ��������� �� ������ ����� </summary>
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

	///<summary> �������� ������������ �� ���� ��� ������ ����� ///</summary>
	bool DatabaseUpdate(const int nId, const CITIES& recCity);
	///<summary >������� �� ���� ��� ������ ����� ///</summary>
	bool DatabaseInsert(const CString& strCityName, const CString& strCityRegion);
	///<summary >���� ���� �� ������ ����� ///</summary>
	bool DatabaseDelete(const int nId);
	///<summary >������ ���� �� ������ ����� ///</summary>
	bool DatabaseSelectById(const long nId);
	///<summary >������ ������ ������� �� ������ ����� ///</summary>
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
#pragma once

#include "SmartArray.h"
#include "CommonDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> ���� �� extend-���� �� �������� �� CDocument, � ��� ������ � ��������� �� ������ ����� </summary>
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

	///<summary> �������� ������������ �� ���� ���s ������ ����� ///</summary>
	bool DatabaseUpdate(const int nId, const CITIES& recCity);
	///<summary >������� �� ���� ��� ������ ����� ///</summary>
	bool DatabaseInsert(CITIES& recItem);
	///<summary >���� ���� �� ������ ����� ///</summary>
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
#pragma once
#include "SmartArray.h"
#include "CommonDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData
/// <summary> ���� �� extend-���� �� �������� �� CDocument, � ��� ������ � ��������� �� ������ ����� </summary>
class CCitiesDoc : public CCommonDocument
{
// Defines
// ----------------
DECLARE_DYNCREATE(CCitiesDoc)
DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
protected:
	CCitiesDoc() noexcept;
public:
	virtual ~CCitiesDoc();

// Methods
// ----------------
public:
	bool SelectById(const long nId, CITIES& recCity);
	bool SelectAll();
	bool Insert(CITIES& recItem);
	bool Delete(const int nId);
	bool Update(const CITIES& recItem);

// Overrides
// ----------------
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Members
// ----------------
public:
	CSmartArray<CITIES> m_oInitialCitiesArray;
	int m_SelectByIdTarget = -1;
};
#pragma once
#include "PhoneTypes.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> ���� �� extend-���� �� �������� �� CDocument, � ��� ������ � ��������� �� ������ ����� </summary>
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
public:
	bool DatabaseSelectById(const long nId);
	bool DatabaseSelectAll();
	bool DatabaseInsert(PHONE_TYPES& recItem);
	bool DatabaseDelete(const int nId);
	bool DatabaseUpdate(const PHONE_TYPES& recItem);
};
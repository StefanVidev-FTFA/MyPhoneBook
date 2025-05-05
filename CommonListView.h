#pragma once
#include <initializer_list>
#include "pch.h"
#include "CitiesDoc.h"
#include <afx.h>
#include "afxcoll.h"
#include "afxtempl.h"

/////////////////////////////////////////////////////////////////////////////
// CCommonListView
///<summary> ���� ������ �� ������������� �� ������ ������ ����� ���������� ������� ///</summary>
class CCommonListView : public CListView
{
// Constants
// ----------------
public:
	enum ListViewHintTypes
	{
		ListViewHintTypesLoadInit = 0,
		ListViewHintTypesInsert,
		ListViewHintTypesSelectById,
		ListViewHintTypesSelectAll,
		ListViewHintTypesUpdateById,
		ListViewHintTypesDelete
	};

// Defines
// ----------------
	DECLARE_DYNCREATE(CCommonListView)

// Constructor / Destructor
// ----------------
protected:
	CCommonListView() noexcept;
public:
	virtual ~CCommonListView();

// Methods
// ----------------
protected:
	void DeclareColumns(const std::initializer_list<CString>& strColumnNames);

// Overrides
// ----------------
protected:
	virtual void OnInitialUpdate();
	virtual void SetViewStyle();
	virtual void CreateListOnInit();

// Members
// ----------------
	CListCtrl* m_pListCtrl;
};
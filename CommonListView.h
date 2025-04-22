#pragma once
#include "pch.h"
#include "CitiesArray.h"
#include "CitiesDoc.h"
#include <afx.h>
#include "afxcoll.h"
#include "afxtempl.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCommonListView

///<summary> Клас служещ за представянето на сходни методи между различните изгледи ///</summary>
class CCommonListView : public CListView
{

	// Constructor / Destructor
	// ----------------
protected:
	CCommonListView() noexcept;
	DECLARE_DYNCREATE(CCommonListView)
public:
	virtual ~CCommonListView();



	//Methods
protected:
	virtual void OnInitialUpdate();

	virtual void SetViewStyle();

	void DeclareColumns(const initializer_list<CString>& strColumnNames);

	//Members
	CListCtrl* m_pListCtrl;
};
#pragma once
#include "CitiesArray.h"
#include "CitiesDoc.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCommonListView

///<summary> ���� ������ �� ������������� �� ������ ������ ����� ���������� ������� ///</summary>
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

	virtual void DeclareColumns(const initializer_list<CString>& strColumnNames);

	//Members
	CListCtrl* m_pListCtrl;
};
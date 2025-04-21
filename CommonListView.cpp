#include "pch.h"
#include "CommonListView.h"


IMPLEMENT_DYNCREATE(CCommonListView, CListView)

CCommonListView::CCommonListView() noexcept{}

CCommonListView::~CCommonListView(){}

void CCommonListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	m_pListCtrl = &GetListCtrl();
}

void CCommonListView::SetViewStyle()
{
	m_pListCtrl->ModifyStyle(0, LVS_REPORT);
	m_pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CCommonListView::DeclareColumns(const initializer_list<CString>& strColumnNames)
{
    int i = 0;
    for (const CString& columnName : strColumnNames)
    {
        m_pListCtrl->InsertColumn(i, columnName, LVCFMT_CENTER, 140);
        i++;
    }
}
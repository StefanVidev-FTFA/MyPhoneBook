#pragma once

#include "pch.h"
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>  // For CListView
#include "framework.h"
#include "PhoneBook.h"
#include "CitiesDoc.h"
#include "CitiesView.h"
#include "CitiesInsertOrUpdateDialog.h"
#include "CDialogFindCityById.h"
#include "Macros.h"
#include "CommonMethods.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CitiesHint.h"
#include "PhoneNumbersView.h"




IMPLEMENT_DYNCREATE(CPhoneNumbersView, CListView)
BEGIN_MESSAGE_MAP(CPhoneNumbersView, CListView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

CPhoneNumbersView::CPhoneNumbersView() noexcept {}
CPhoneNumbersView::~CPhoneNumbersView() {}


BOOL CPhoneNumbersView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}
void CPhoneNumbersView::SetViewStyle()
{
	m_pListCtrl->ModifyStyle(0, LVS_REPORT);
	m_pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CPhoneNumbersView::OnInitialUpdate()
{
	CCommonListView::OnInitialUpdate();
	m_pListCtrl = &GetListCtrl();

	CCitiesDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);

	CSmartArray<CITIES>& oCitiesArray = oDocument->m_oInitialCitiesArray;


	if (oCitiesArray.IsEmpty()) {
		AfxMessageBox(_T("There was no phone numbers to load in Init"), MB_ICONERROR);
	}
	else
	{
		SetViewStyle();

		DeclareColumns({ _T("ID"),_T("pn column 1"),_T("pn column 2") });

		//InsertCityRows(oCitiesArray);

		//for (INT_PTR i = 0; i < oCitiesArray.GetCount(); ++i) {
		//	CITIES* pRecCity = static_cast<CITIES*>(oCitiesArray.GetAt(i));
		//	if (pRecCity != nullptr) {
		//		CString sId;
		//		sId.Format(_T("%d"), pRecCity->nId);
		//		int row = m_pListCtrl->InsertItem(i, sId);
		//		m_pListCtrl->SetItemText(i, 1, CString(pRecCity->szCityName));
		//		m_pListCtrl->SetItemText(row, 2, CString(pRecCity->szRegion));
		//		//entriesMap.SetAt(pRecCity->nId, i);
		//	}
		//}
	}
}


void CPhoneNumbersView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhoneNumbersView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	CPoint clientPoint = point;
	ScreenToClient(&clientPoint);

	UINT flags = 0;

	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


#ifdef _DEBUG
void CPhoneNumbersView::AssertValid() const
{
	CListView::AssertValid();
}

void CPhoneNumbersView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CPhoneNumbersView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG
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
#include "PhoneNumbers.h"
#include "PhoneNumbersDoc.h"




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

void CPhoneNumbersView::OnInitialUpdate()
{
	CCommonListView::OnInitialUpdate();
	m_pListCtrl = &GetListCtrl();

	CPhoneNumbersDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);

	CSmartArray<PHONE_NUMBERS>& oPhoneNumbersArray = oDocument->m_oInitialPhoneNumbersArray;


	if (oPhoneNumbersArray.IsEmpty()) {
		AfxMessageBox(_T("There was no phone numbers to load in Init"), MB_ICONERROR);
	}
	else
	{
		SetViewStyle();

		DeclareColumns({ _T("ID"),_T("Person ID"),_T("Phone type ID"),_T("Phone number") });

		InsertCityRows(oPhoneNumbersArray);
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

CPhoneNumbersDoc* CPhoneNumbersView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneNumbersDoc)));
	return (CPhoneNumbersDoc*)m_pDocument;
}

#endif //_DEBUG
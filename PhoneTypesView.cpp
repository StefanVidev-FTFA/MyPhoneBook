#include "pch.h"
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h> 
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
#include "PhoneTypesView.h"
#include "PhoneTypes.h"
#include "PhoneTypesDoc.h"




IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)
BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


CPhoneTypesView::CPhoneTypesView() noexcept {}
CPhoneTypesView::~CPhoneTypesView() {}


BOOL CPhoneTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

void CPhoneTypesView::CreateListOnInit()
{
	CSmartArray<PHONE_TYPES>& oPhoneTypesArray = GetDocument()->m_oInitialPhoneTypesArray;

	SetViewStyle();

	DeclareColumns({ _T("ID"),_T("Phone type") });

	InsertCityRows(oPhoneTypesArray);
}

void CPhoneTypesView::OnInitialUpdate()
{
	CCommonListView::OnInitialUpdate();
	m_pListCtrl = &GetListCtrl();

	CPhoneTypesDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);

	CSmartArray<PHONE_TYPES>& oPhoneTypesArray = oDocument->m_oInitialPhoneTypesArray;


	if (oPhoneTypesArray.IsEmpty()) {
		AfxMessageBox(_T("There was no phone numbers to load in Init"), MB_ICONERROR);
	}
	else
	{
		CreateListOnInit();
	}
}


void CPhoneTypesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhoneTypesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	CPoint clientPoint = point;
	ScreenToClient(&clientPoint);

	UINT flags = 0;

	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


#ifdef _DEBUG
void CPhoneTypesView::AssertValid() const
{
	CListView::AssertValid();
}

void CPhoneTypesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPhoneTypesDoc* CPhoneTypesView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDoc)));
	return (CPhoneTypesDoc*)m_pDocument;
}

#endif //_DEBUG
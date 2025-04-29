#include "pch.h"
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include "framework.h"
#include "PhoneBook.h"
#include "CitiesDoc.h"
#include "CitiesView.h"
#include "Macros.h"
#include "CommonMethods.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "PersonsView.h"
#include "PersonsDoc.h"

IMPLEMENT_DYNCREATE(CPersonsView, CListView)
BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

CPersonsView::CPersonsView() noexcept {}
CPersonsView::~CPersonsView() {}

BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

void CPersonsView::CreateListOnInit()
{
	CSmartArray<PERSONS>& oPersonsArray = GetDocument()->m_oInitialPersonsArray;

	SetViewStyle();

	DeclareColumns({ _T("ID"),_T("First Name"),_T("Middle Name")
		,_T("Last Name"),_T("EGN") ,_T("City ID"),_T("Adress") });

	InsertCityRows(oPersonsArray);
}

void CPersonsView::OnInitialUpdate()
{
	CCommonListView::OnInitialUpdate();
	m_pListCtrl = &GetListCtrl();

	CPersonsDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);

	CSmartArray<PERSONS>& oPersonsArray = oDocument->m_oInitialPersonsArray;


	if (oPersonsArray.IsEmpty()) {
		AfxMessageBox(_T("There was no phone numbers to load in Init"), MB_ICONERROR);
	}
	else
	{
		CreateListOnInit();
	}
}

void CPersonsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPersonsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	CPoint clientPoint = point;
	ScreenToClient(&clientPoint);

	UINT flags = 0;

	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	CListView::AssertValid();
}

void CPersonsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPersonsDoc* CPersonsView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDoc)));
	return (CPersonsDoc*)m_pDocument;
}

#endif //_DEBUG
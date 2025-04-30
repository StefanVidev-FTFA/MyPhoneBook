#include "pch.h"
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include "framework.h"
#include "PhoneBook.h"
#include "Macros.h"
#include "CommonMethods.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "PersonsView.h"
#include "PersonsDoc.h"
#include "DialogPersonsInsert.h"

using namespace std;

IMPLEMENT_DYNCREATE(CPersonsView, CListView)
BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_SELECTALL, &CPersonsView::RequestSelectAll)
	ON_COMMAND(ID_EDIT_INSERTROW, &CPersonsView::RequestInsert)
END_MESSAGE_MAP()

CPersonsView::CPersonsView() noexcept {}
CPersonsView::~CPersonsView() {}

void CPersonsView::RequestSelectAll() {

	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to select all?"));

	int nResult = AfxMessageBox(strMessage, MB_YESNO);

	if (nResult == IDYES)
	{
		GetDocument()->DatabaseSelectAll();
	}
}

void CPersonsView::RequestInsert()
{

	CStringList citiesIdsList;

	CCitiesTable oCitiesTable;

	oCitiesTable.AssignAllCityIds(citiesIdsList);

	DialogPersonsInsert oDialog(citiesIdsList);

	INT_PTR result = oDialog.DoModal();

	if (result == IDOK)
	{
		//GetDocument()->DatabaseInsert(oDialog.m_recCityForInsertOrUpdate);
	}
}

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

void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListView::OnUpdate(pSender, lHint, pHint);
	m_pListCtrl = &GetListCtrl();

	CPersonsDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);


	if (lHint == SqlOperationInsert)
	{
	}
	else if (lHint == SqlOperationSelectById)
	{
	}
	else if (lHint == SqlOperationSelectAll)
	{
		CSmartArray<PERSONS>* pPersonsHint = dynamic_cast<CSmartArray<PERSONS>*>(pHint);

		m_pListCtrl->DeleteAllItems();
		InsertCityRows(*pPersonsHint);
	}
	else if (lHint == SqlOperationUpdateById)
	{
	}
	else if (lHint == SqlOperationDelete)
	{
		m_pListCtrl->DeleteItem(m_SelectedIndex);
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
	int clickedIndex = m_pListCtrl->HitTest(clientPoint, &flags);

	if (clickedIndex != -1 && (flags & LVHT_ONITEM)) {

		m_pListCtrl->SetItemState(clickedIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_SelectedIndex = clickedIndex;

	}
	else {
		m_SelectedIndex = -1;
	}

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
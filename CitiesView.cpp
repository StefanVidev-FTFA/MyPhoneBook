
// CitiesView.cpp : implementation of the CCitiesView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CitiesDoc.h"
#include "CitiesView.h"
#include "CCitiesInsertDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCitiesView

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_INSERTROW, &CCitiesView::OnInsert)
	ON_COMMAND(ID_EDIT_DELETEROW32774, &CCitiesView::OnDelete)
END_MESSAGE_MAP()


CCitiesView::CCitiesView() noexcept{}
CCitiesView::~CCitiesView(){}


void CCitiesView::OnInsert()
{


	CCitiesData& oCitiesData = GetDocument()->m_oCitiesData;

	CCitiesInsertDlg oInsertDlg;

	if (oInsertDlg.DoModal() == IDOK) {
		AfxMessageBox(_T("Insert Dialog returned OK"));
	}
	if (oInsertDlg.DoModal() == IDCANCEL) {
		AfxMessageBox(_T("Insert Dialog returned CANCEL"));
	}

}
void CCitiesView::OnDelete()
{
	AfxMessageBox(_T("OnDelete()"));
}

void CCitiesView::SetViewStyle()
{
	m_pListCtrl->ModifyStyle(0, LVS_REPORT);
	m_pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}
void CCitiesView::DeclareCityColums(int nAlignment)
{
	m_pListCtrl->InsertColumn(COLUMN_ID, _T("ID"), nAlignment, 35);
	m_pListCtrl->InsertColumn(COLUMN_CITY_NAME, _T("City"), nAlignment, 110);
	m_pListCtrl->InsertColumn(COLUMN_CITY_REGION, _T("Region"), nAlignment, 150);
}
void CCitiesView::InsertCityRows(CCitiesArray& oCitiesArray)
{
	for (int i = 0; i < oCitiesArray.GetSize(); ++i) {

		CITIES* pRecCity = static_cast<CITIES*>(oCitiesArray.GetAt(i));

		if (pRecCity != nullptr) {

			CString sId;
			sId.Format(_T("%d"), pRecCity->nId);


			int row = m_pListCtrl->InsertItem(i, sId);
			m_pListCtrl->SetItemText(i, 1, CString(pRecCity->szCityName));
			m_pListCtrl->SetItemText(row, 2, CString(pRecCity->szRegion));
		}
	}
}

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	m_pListCtrl = &GetListCtrl();

	CCitiesDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);

	CCitiesArray& oCitiesArray = oDocument->m_oInitialCitiesArray;


	if (oCitiesArray.IsEmpty()) {
		AfxMessageBox(_T("There was no cities to load in Init"), MB_ICONERROR);
	}
	else
	{
		SetViewStyle();
		DeclareCityColums(LVCFMT_CENTER);
		InsertCityRows(oCitiesArray);
	}
}

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCitiesView diagnostics

#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers

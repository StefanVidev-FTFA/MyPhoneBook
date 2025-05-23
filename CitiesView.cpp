
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
#include "CDialogFindCityById.h"


// CCitiesView

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_INSERTROW, &CCitiesView::OnInsert)
	ON_COMMAND(ID_EDIT_DELETEROW32774, &CCitiesView::OnDelete)
	ON_COMMAND(ID_EDIT_SELECTBYID, &CCitiesView::SelectById)
	ON_COMMAND(ID_EDIT_SELECTALL, &CCitiesView::SelectAll)
	ON_COMMAND(ID_EDIT_UPDATEBYID, &CCitiesView::UpdateById)
END_MESSAGE_MAP()
//ID_EDIT_SELECTALL


CCitiesView::CCitiesView() noexcept{}
CCitiesView::~CCitiesView(){}


void CCitiesView::OnInsert()
{
	CCitiesData* oCitiesData = ((CCitiesDoc*)GetDocument())->m_oCitiesData;


	CCitiesInsertDlg oInsertDlg(this,oCitiesData);

	INT_PTR result = oInsertDlg.DoModal();

	if (result == IDOK) {
		AfxMessageBox(_T("Insert Dialog returned OK"));
	}
	else if (result == IDCANCEL) {
		AfxMessageBox(_T("Insert Dialog returned CANCEL"));
	}

	GetDocument()->UpdateAllViews(nullptr, INSERT_OR_DELETE, nullptr);

}
void CCitiesView::OnDelete()
{

	CCitiesDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);

	CCitiesArray& oCitiesArray = oDocument->m_oInitialCitiesArray;


	CITIES* pRecCity = static_cast<CITIES*>(oCitiesArray.GetAt(m_SelectedIndex));


	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to delete this row\n\n"
									"- ID:   %d\n"
									"- City Name:   %s\n"
									"- City Region:   %s\n"
								),
		pRecCity->nId,CString(pRecCity->szCityName),CString(pRecCity->szRegion));


	int nResult = AfxMessageBox(strMessage, MB_YESNO);


	if (nResult == IDYES)
	{
		//CCitiesData* oCitiesData = ((CCitiesDoc*)GetDocument())->m_oCitiesData;


		CCitiesData oCitiesData;

		oCitiesData.DeleteWhereID(pRecCity->nId);


		oDocument->UpdateAllViews(nullptr,1,nullptr);

	}



}
void CCitiesView::SelectById() {
	CDialogFindCityById oSelectByIdDlg;

	INT_PTR result = oSelectByIdDlg.DoModal();

	if (result == IDOK) {


		m_nIdToBeSelected = oSelectByIdDlg.m_nIdToBeSelected;


		GetDocument()->UpdateAllViews(nullptr, SELECT_BY_ID, nullptr);

	}

}
void CCitiesView::SelectAll() {

	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to select all?"));


	int nResult = AfxMessageBox(strMessage, MB_YESNO);


	if (nResult == IDYES)
	{
		GetDocument()->UpdateAllViews(nullptr, SELECT_ALL, nullptr);
	}

}
void CCitiesView::UpdateById()
{
	CDialogFindCityById oSelectByIdDlg;

	INT_PTR result = oSelectByIdDlg.DoModal();

	if (result == IDOK) {


		m_nIdToBeSelected = oSelectByIdDlg.m_nIdToBeSelected;
		CCitiesData* oCitiesData = ((CCitiesDoc*)GetDocument())->m_oCitiesData;

		CCitiesInsertDlg oUpdateDlg(this, oCitiesData);

		INT_PTR result = oUpdateDlg.DoModal();
		
		if (result == IDOK) {
			AfxMessageBox(_T("Update Dialog returned OK"));
		}
		else if (result == IDCANCEL) {
			AfxMessageBox(_T("Update Dialog returned CANCEL"));
		}

		GetDocument()->UpdateAllViews(nullptr, SELECT_ALL, nullptr);

	}
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
void CCitiesView::InsertACityRow(CITIES& recCity) {
	if (recCity.nId>-1) {

		CString sId;
		sId.Format(_T("%d"), recCity.nId);


		int row = m_pListCtrl->InsertItem(0, sId);
		m_pListCtrl->SetItemText(0, 1, CString(recCity.szCityName));
		m_pListCtrl->SetItemText(row, 2, CString(recCity.szRegion));
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
void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListView::OnUpdate(pSender, lHint, pHint);
	m_pListCtrl = &GetListCtrl();

	CCitiesDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);


	if (lHint == INSERT_OR_DELETE)
	{
		CCitiesData data;
		CCitiesArray oCitiesArray;
		data.SelectAll(oCitiesArray);

		if (oCitiesArray.IsEmpty()) {
			AfxMessageBox(_T("There was no cities to load"), MB_ICONERROR);
		}
		else
		{
			m_pListCtrl->DeleteAllItems();
			InsertCityRows(oCitiesArray);
		}

	}
	else if (lHint == SELECT_BY_ID)
	{
		CCitiesData data;
		CITIES recFoundCity;

		data.SelectWhereID(m_nIdToBeSelected, recFoundCity);
		if (recFoundCity.nId > -1)
		{
			m_pListCtrl->DeleteAllItems();
			InsertACityRow(recFoundCity);
		}

	}
	else if (lHint == SELECT_ALL)
	{
		m_pListCtrl = &GetListCtrl();

		CCitiesDoc* oDocument = GetDocument();
		ASSERT_VALID(oDocument);




		CCitiesArray oCitiesArray;
		CCitiesData oCitiesData;

		oCitiesData.SelectAll(oCitiesArray);


		if (oCitiesArray.IsEmpty()) {
			AfxMessageBox(_T("There was no cities to load for Select all"), MB_ICONERROR);
		}
		else
		{
			m_pListCtrl->DeleteAllItems();
			InsertCityRows(oCitiesArray);
		}
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
	// Convert to client coords for HitTest
	CPoint clientPoint = point;
	ScreenToClient(&clientPoint);

	UINT flags = 0;
	int clickedIndex = m_pListCtrl->HitTest(clientPoint, &flags);

	if (clickedIndex != -1 && (flags & LVHT_ONITEM)) {
		// Optional: visually select the item
		m_pListCtrl->SetItemState(clickedIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

		// Save the clicked index so your delete handler knows which to remove
		m_SelectedIndex = clickedIndex;
	}
	else {
		m_SelectedIndex = -1; // Nothing clicked
	}

	// Show the menu
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

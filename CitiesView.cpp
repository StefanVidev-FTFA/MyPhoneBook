#pragma once
#include "pch.h"
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

IMPLEMENT_DYNCREATE(CCitiesView, CListView)
BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_INSERTROW, &CCitiesView::RequestInsert)
	ON_COMMAND(ID_EDIT_DELETEROW32774, &CCitiesView::RequestDelete)
	ON_COMMAND(ID_EDIT_SELECTBYID, &CCitiesView::RequestSelectById)
	ON_COMMAND(ID_EDIT_SELECTALL, &CCitiesView::RequestSelectAll)
	ON_COMMAND(ID_EDIT_UPDATEBYID, &CCitiesView::RequestUpdate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCitiesView

	// Constructor / Destructor
	// ----------------
CCitiesView::CCitiesView() noexcept{}
CCitiesView::~CCitiesView(){}

	// Methods
	// ----------------
void CCitiesView::RequestSelectById()
{
	CDialogFindCityById oSelectByIdDlg;
	INT_PTR result = oSelectByIdDlg.DoModal();

	if (result == IDOK)
	{
		m_nIdToBeSelected = oSelectByIdDlg.m_nIdToBeSelected;

		if (m_nIdToBeSelected > -1) 
		{
			GetDocument()->DatabaseSelectById(m_nIdToBeSelected);
		}
		else
		{
			AfxMessageBox(_T("Sorry! Did not find a city with this ID"));
		}
	}
}

void CCitiesView::RequestSelectAll() {

	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to select all?"));


	int nResult = AfxMessageBox(strMessage, MB_YESNO);


	if (nResult == IDYES)
	{
		CCitiesDoc* oCitiesDocument = GetDocument();

		oCitiesDocument->DatabaseSelectAll();
	}

}

void CCitiesView::RequestInsert()
{
	CCitiesData* oCitiesData = ((CCitiesDoc*)GetDocument())->m_oCitiesData;


	CCitiesInsertOrUpdateDialog oInsertDlg;

	INT_PTR result = oInsertDlg.DoModal();

	if (result == IDOK)
	{
		GetDocument()->DatabaseInsert(oInsertDlg.m_strCityName, oInsertDlg.m_strCityRegion);
	}
}

void CCitiesView::RequestDelete()
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
		oDocument->DatabaseDelete(pRecCity->nId);
	}
}

void CCitiesView::RequestUpdate()
{
	int nResult = AfxMessageBox(_T("Are you sure you wish to update this row?"), MB_YESNO);

	if (nResult == IDYES)
	{
		long nId = -1;

		CCitiesArray& oCitiesArray = GetDocument()->m_oInitialCitiesArray;
		CITIES* pRecCity = static_cast<CITIES*>(oCitiesArray.GetAt(m_SelectedIndex));

		nId = pRecCity->nId;

		if (nId > -1)
		{
			CCitiesInsertOrUpdateDialog oInsertDlg;

			INT_PTR result = oInsertDlg.DoModal();

			if (result == IDOK)
			{
				CITIES recCityforUpdate = oInsertDlg.m_recCityForUpdate;
				CCitiesDoc* oCitiesDocument = GetDocument();

				oCitiesDocument->DatabaseUpdate(nId, recCityforUpdate);
			}
		}
	}
}

void CCitiesView::SetViewStyle()
{
	m_pListCtrl->ModifyStyle(0, LVS_REPORT);
	m_pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CCitiesView::DeclareCityColums(int nAlignment)
{
	m_pListCtrl->InsertColumn(CityColumnId, _T("ID"), nAlignment, 35);
	m_pListCtrl->InsertColumn(CityColumnName, _T("City"), nAlignment, 110);
	m_pListCtrl->InsertColumn(CityColumnRegion, _T("Region"), nAlignment, 150);
}

void CCitiesView::InsertCityRows(CCitiesArray& oCitiesArray)
{
	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); ++i) {

		CITIES* pRecCity = static_cast<CITIES*>(oCitiesArray.GetAt(i));

		if (pRecCity != nullptr) {

			CString sId;
			sId.Format(_T("%d"), pRecCity->nId);


			int row = m_pListCtrl->InsertItem(i, sId);
			m_pListCtrl->SetItemText(i, 1, CString(pRecCity->szCityName));
			m_pListCtrl->SetItemText(row, 2, CString(pRecCity->szRegion));

			entriesMap.SetAt(pRecCity->nId, i);
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


	if (lHint == SqlOperationInsert)
	{
		CCitiesHint* pCitiesHint = dynamic_cast<CCitiesHint*>(pHint);
		int index = m_pListCtrl->InsertItem(m_pListCtrl->GetItemCount(),_T("-"));

		m_pListCtrl->SetItemText(index, 1, CString(pCitiesHint->m_recCity.szCityName));
		m_pListCtrl->SetItemText(index, 2, CString(pCitiesHint->m_recCity.szRegion));
	}
	else if (lHint == SqlOperationSelectById)
	{
		CCitiesHint* pCitiesHint = dynamic_cast<CCitiesHint*>(pHint);

		if (pCitiesHint->m_nTargetId > -1)
		{
			m_pListCtrl->DeleteAllItems();
			InsertACityRow(pCitiesHint->m_recCity);
		}
	}
	else if (lHint == SqlOperationSelectAll)
	{
		CCitiesArray* pCitiesHint = dynamic_cast<CCitiesArray*>(pHint);

		m_pListCtrl->DeleteAllItems();
		InsertCityRows(*pCitiesHint);
	}
	else if (lHint == SqlOperationUpdateById)
	{
		CCitiesHint* pCitiesHint = dynamic_cast<CCitiesHint*>(pHint);

		int nRowIndex = -1;
		entriesMap.Lookup(pCitiesHint->m_nTargetId, nRowIndex);

		m_pListCtrl->SetItemText(nRowIndex, 1, CString(pCitiesHint->m_recCity.szCityName));
		m_pListCtrl->SetItemText(nRowIndex, 2, CString(pCitiesHint->m_recCity.szRegion));

	}
	else if (lHint == SqlOperationDelete)
	{
		CCitiesData data;
		CCitiesArray oCitiesArray;
		data.SelectAll(oCitiesArray);

		if (oCitiesArray.IsEmpty()) {
			MESSAGE_WARNING(_T("There was no cities to load"), MB_ICONERROR);
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


#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG
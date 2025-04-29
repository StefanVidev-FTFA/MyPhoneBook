#pragma once
#include "pch.h"
#include "framework.h"
#include "PhoneBook.h"
#include "CitiesDoc.h"
#include "CitiesView.h"
#include "Macros.h"
#include "CommonMethods.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CitiesHint.h"
#include "GeneralHint.h"
#include "CDialogCities.h"

IMPLEMENT_DYNCREATE(CCitiesView, CListView)
BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_INSERTROW, &CCitiesView::RequestInsert)
	ON_COMMAND(ID_EDIT_DELETEROW32774, &CCitiesView::RequestDelete)
	ON_COMMAND(ID_EDIT_SELECTBYID, &CCitiesView::RequestSelectById)
	ON_COMMAND(ID_EDIT_SELECTALL, &CCitiesView::RequestSelectAll)
	ON_COMMAND(ID_EDIT_UPDATEBYID, &CCitiesView::RequestUpdate)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCitiesView

	// Constructor / Destructor
	// ----------------
CCitiesView::CCitiesView() noexcept{}
CCitiesView::~CCitiesView(){}

	// Methods
	// ----------------

void CCitiesView::CreateListOnInit()
{

}

void CCitiesView::RequestSelectById()
{
	CITIES recCity;

	wcscpy_s(recCity.szCityName, MAX_CITY_NAME, m_pListCtrl->GetItemText(m_SelectedIndex, 1));
	wcscpy_s(recCity.szRegion, MAX_REGION_NAME, m_pListCtrl->GetItemText(m_SelectedIndex, 2));


	CDialogCities oSelectByIdDlg(recCity,CCommonListView::DialogModeView);

	INT_PTR result = oSelectByIdDlg.DoModal();
}

void CCitiesView::RequestSelectAll() {

	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to select all?"));

	int nResult = AfxMessageBox(strMessage, MB_YESNO);

	if (nResult == IDYES)
	{
		CCitiesDoc* oCitiesDocument = GetDocument();

		GetDocument()->DatabaseSelectAll();
	}
}

void CCitiesView::RequestInsert()
{
	CITIES recCity;
	CDialogCities oDialog(recCity, CCommonListView::DialogModeEdit);
	INT_PTR result = oDialog.DoModal();

	if (result == IDOK)
	{
		GetDocument()->DatabaseInsert(oDialog.m_recCityForInsertOrUpdate);
	}
}

void CCitiesView::RequestDelete()
{
	CCitiesDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);
	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to delete this row\n\n"
									"- ID:   %s\n"
									"- City Name:   %s\n"
									"- City Region:   %s\n"
								),
					m_pListCtrl->GetItemText(m_SelectedIndex,0),
					m_pListCtrl->GetItemText(m_SelectedIndex, 1),
					m_pListCtrl->GetItemText(m_SelectedIndex, 2)
					);
	int nResult = AfxMessageBox(strMessage, MB_YESNO);
	if (nResult == IDYES)
	{
		CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
		long nId = _ttol(strValue);
		oDocument->DatabaseDelete(nId);
	}
}

void CCitiesView::RequestUpdate()
{
	int nResult = AfxMessageBox(_T("Are you sure you wish to update this row?"), MB_YESNO);

	if (nResult == IDYES)
	{
		CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
		long nId = _ttol(strValue);

		if (nId > -1)
		{
			CITIES recCity;
			CDialogCities oDialog(recCity, CCommonListView::DialogModeEdit);
			INT_PTR result = oDialog.DoModal();

			if (result == IDOK)
			{
				oDialog.m_recCityForInsertOrUpdate.nId = nId;
				GetDocument()->DatabaseUpdate(oDialog.m_recCityForInsertOrUpdate);
			}
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
	CCommonListView::OnInitialUpdate();

	CCitiesDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);


	CSmartArray<CITIES>& oCitiesArray = oDocument->m_oInitialCitiesArray;


	if (oCitiesArray.IsEmpty()) {
		AfxMessageBox(_T("There was no cities to load in Init"), MB_ICONERROR);
	}
	else
	{
		SetViewStyle();

		DeclareColumns({ _T("ID"),_T("City Name"),_T("City Region") });

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
		CGeneralHint<CITIES>* pCitiesHint = dynamic_cast<CGeneralHint<CITIES>*>(pHint);

		CITIES recItem = pCitiesHint->m_recItem;

		CString strId;

		strId.Format(_T("%d"), recItem.nId);

		int index = m_pListCtrl->InsertItem(m_pListCtrl->GetItemCount(), strId);

		m_pListCtrl->SetItemText(index, 1, CString(pCitiesHint->m_recItem.szCityName));
		m_pListCtrl->SetItemText(index, 2, CString(pCitiesHint->m_recItem.szRegion));
	}
	else if (lHint == SqlOperationSelectById)
	{
		CGeneralHint<CITIES>* pCitiesHint = dynamic_cast<CGeneralHint<CITIES>*>(pHint);

		if (pCitiesHint->m_recItem.nId > -1)
		{
			m_pListCtrl->DeleteAllItems();
			InsertACityRow(pCitiesHint->m_recItem);
		}
	}
	else if (lHint == SqlOperationSelectAll)
	{
		CSmartArray<CITIES>* pCitiesHint = dynamic_cast<CSmartArray<CITIES>*>(pHint);

		m_pListCtrl->DeleteAllItems();
		InsertCityRows(*pCitiesHint);
	}
	else if (lHint == SqlOperationUpdateById)
	{
		CGeneralHint<CITIES>* pCitiesHint = dynamic_cast<CGeneralHint<CITIES>*>(pHint);

		CITIES recCity = pCitiesHint->m_recItem;

		//int nRowIndex = -1;
		//entriesMap.Lookup(recCity.nId, nRowIndex);

		m_pListCtrl->SetItemText(m_SelectedIndex, 1, CString(recCity.szCityName));
		m_pListCtrl->SetItemText(m_SelectedIndex, 2, CString(recCity.szRegion));
	}
	else if (lHint == SqlOperationDelete)
	{
		m_pListCtrl->DeleteItem(m_SelectedIndex);
	}
}

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCitiesView::OnLButtonDblClk(UINT /* nFlags */, CPoint point)
{
	MESSAGE_INFO(_T("OnLButtonDblClk"));
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
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
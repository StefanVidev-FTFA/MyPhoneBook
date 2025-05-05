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
#include "GeneralHint.h"
#include "DialogCities.h"

// Defines
// ----------------
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

// Constructor / Destructor
// ----------------
CCitiesView::CCitiesView() noexcept{}
CCitiesView::~CCitiesView(){}

// Methods
// ----------------
void CCitiesView::InsertRows(CSmartArray<CITIES>& oCitiesArray)
 {
	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); ++i)
	{
		CITIES* pRecItem = static_cast<CITIES*>(oCitiesArray.GetAt(i));

		if (pRecItem == nullptr)
			continue;

			CString sId;
			sId.Format(_T("%d"), pRecItem->nId);

			INT_PTR row = m_pListCtrl->InsertItem(i, sId);
			m_pListCtrl->SetItemText(i, 1, CString(pRecItem->szCityName));
			m_pListCtrl->SetItemText(row, 2, CString(pRecItem->szRegion));

			entriesMap.SetAt(pRecItem->nId, i);
	}
}
void CCitiesView::CreateListOnInit()
{
}

void CCitiesView::RequestSelectById()
{
	CITIES recCity;

	CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
	long nId = _ttol(strValue);

	if (!GetDocument()->SelectById(nId, recCity))
		return;

	CDialogCities oSelectByIdDlg(recCity,DialogModeView);

	INT_PTR result = oSelectByIdDlg.DoModal();
}
void CCitiesView::RequestSelectAll() {

	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to select all?"));

	int nResult = AfxMessageBox(strMessage, MB_YESNO);

	if (nResult == IDYES)
	{
		CCitiesDoc* oCitiesDocument = GetDocument();

		GetDocument()->SelectAll();
	}
}
void CCitiesView::RequestInsert()
{
	CITIES recCity;
	CDialogCities oDialog(recCity, DialogModeEdit);
	INT_PTR result = oDialog.DoModal();

	if (result == IDOK)
	{
		GetDocument()->Insert(oDialog.m_recCityForInsertOrUpdate);
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
		oDocument->Delete(nId);
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

			wcscpy_s(recCity.szCityName, MAX_CITY_NAME, m_pListCtrl->GetItemText(m_SelectedIndex, 1));
			wcscpy_s(recCity.szRegion, MAX_REGION_NAME, m_pListCtrl->GetItemText(m_SelectedIndex, 2));

			CDialogCities oDialog(recCity, DialogModeEdit);
			INT_PTR result = oDialog.DoModal();

			if (result == IDOK)
			{
				oDialog.m_recCityForInsertOrUpdate.nId = nId;
				GetDocument()->Update(oDialog.m_recCityForInsertOrUpdate);
			}
		}
	}
}

void CCitiesView::InsertACityRow(CITIES& recCity) {
	CString strCityID;
	strCityID.Format(_T("%d"), recCity.nId);

	const int row = m_pListCtrl->InsertItem(0, strCityID);
	m_pListCtrl->SetItemText(0, 1, CString(recCity.szCityName));
	m_pListCtrl->SetItemText(row, 2, CString(recCity.szRegion));
}

// OVerrides
// ----------------
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
		return;
	}

	SetViewStyle();
	
	DeclareColumns({ _T("ID"),_T("City Name"),_T("City Region") });
	
	InsertRows(oCitiesArray);
}
void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListView::OnUpdate(pSender, lHint, pHint);
	m_pListCtrl = &GetListCtrl();

	CCitiesDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);


	if (lHint == ListViewHintTypesInsert)
	{
		CGeneralHint<CITIES>* pCitiesHint = dynamic_cast<CGeneralHint<CITIES>*>(pHint);
		// да се изтрие или да бъде в stack-a pCitiesHint
		CITIES recItem = pCitiesHint->m_recItem;

		CString strId;

		strId.Format(_T("%d"), recItem.nId);

		int index = m_pListCtrl->InsertItem(m_pListCtrl->GetItemCount(), strId);

		m_pListCtrl->SetItemText(index, 1, CString(pCitiesHint->m_recItem.szCityName));
		m_pListCtrl->SetItemText(index, 2, CString(pCitiesHint->m_recItem.szRegion));
	}
	else if (lHint == ListViewHintTypesSelectAll)
	{
		CSmartArray<CITIES>* pCitiesHint = dynamic_cast<CSmartArray<CITIES>*>(pHint);

		m_pListCtrl->DeleteAllItems();
		InsertRows(*pCitiesHint);
	}
	else if (lHint == ListViewHintTypesUpdateById)
	{
		CGeneralHint<CITIES>* pCitiesHint = dynamic_cast<CGeneralHint<CITIES>*>(pHint);
		CITIES recCity = pCitiesHint->m_recItem;

		m_pListCtrl->SetItemText(m_SelectedIndex, 1, CString(recCity.szCityName));
		m_pListCtrl->SetItemText(m_SelectedIndex, 2, CString(recCity.szRegion));
	}
	else if (lHint == ListViewHintTypesDelete)
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
	CListCtrl& listCtrl = GetListCtrl();

	LVHITTESTINFO hitTestInfo = {};
	hitTestInfo.pt = point;

	int rowIndex = listCtrl.HitTest(&hitTestInfo);

	if(rowIndex!=-1)
	{
		m_SelectedIndex = rowIndex;
		CCitiesView::RequestSelectById();
	}
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

	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, 
		point.x, 
		point.y, 
		this, 
		TRUE);

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
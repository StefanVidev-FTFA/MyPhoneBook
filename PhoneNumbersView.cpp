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
#include "PhoneNumbersView.h"
#include "PhoneNumbers.h"
#include "PhoneNumbersDoc.h"
#include "DialogPhoneNumbers.h"
#include "PhoneNumbersInfo.h"



IMPLEMENT_DYNCREATE(CPhoneNumbersView, CListView)
BEGIN_MESSAGE_MAP(CPhoneNumbersView, CListView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
	//ON_COMMAND(ID_EDIT_INSERTROW, &CPhoneNumbersView::RequestInsert)
	ON_COMMAND(ID_EDIT_DELETEROW32774, &CPhoneNumbersView::RequestDelete)
	ON_COMMAND(ID_EDIT_SELECTBYID, &CPhoneNumbersView::RequestSelectById)
	ON_COMMAND(ID_EDIT_SELECTALL, &CPhoneNumbersView::RequestSelectAll)
	ON_COMMAND(ID_EDIT_UPDATEBYID, &CPhoneNumbersView::RequestUpdate)
END_MESSAGE_MAP()

CPhoneNumbersView::CPhoneNumbersView() noexcept {}
CPhoneNumbersView::~CPhoneNumbersView() {}


BOOL CPhoneNumbersView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

void CPhoneNumbersView::CreateListOnInit()
{
	CSmartArray<PHONE_NUMBERS>& oPhoneNumbersArray = GetDocument()->m_oInitialPhoneNumbersArray;

	SetViewStyle();

	DeclareColumns({ _T("ID"),_T("Person ID"),_T("Phone type ID"),_T("Phone number") });

	InsertCityRows(oPhoneNumbersArray);
}

void CPhoneNumbersView::InsertASingleRow(PHONE_NUMBERS& recItem)
{
	if (recItem.nId > -1) {

		CString strId;
		strId.Format(_T("%d"), recItem.nId);


		int row = m_pListCtrl->InsertItem(0, strId);

		strId.Format(_T("%d"), recItem.nPersonId);
		m_pListCtrl->SetItemText(0, 1, strId);

		strId.Format(_T("%d"), recItem.nPhoneTypeId);
		m_pListCtrl->SetItemText(row, 2, strId);

		m_pListCtrl->SetItemText(row, 3, CString(recItem.szPhoneNumber));
	}
}

void CPhoneNumbersView::RequestSelectAll() {

	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to select all?"));

	int nResult = AfxMessageBox(strMessage, MB_YESNO);

	if (nResult == IDYES)
	{
		CPhoneNumbersDoc* oPhoneNumbersDocument = GetDocument();

		GetDocument()->DatabaseSelectAll();
	}
}

void CPhoneNumbersView::RequestSelectById()
{
	PHONE_NUMBERS recPhoneNum;

	int nId = _ttoi(m_pListCtrl->GetItemText(m_SelectedIndex, 1));

	CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 1);
	recPhoneNum.nPersonId = _ttoi(strValue);

	strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 2);
	recPhoneNum.nPhoneTypeId = _ttoi(strValue);

	wcscpy_s(recPhoneNum.szPhoneNumber, MAX_PHONE_NUMBER, m_pListCtrl->GetItemText(m_SelectedIndex, 3));


	CPhoneNumbersInfo* pInfo = new CPhoneNumbersInfo();

	pInfo->m_recPhoneNum = recPhoneNum;


	CDialogPhoneNumbers oDialog(pInfo, CCommonListView::DialogModeView);
	INT_PTR result = oDialog.DoModal();
	if (result == IDOK)
	{
		GetDocument()->DatabaseSelectById(nId);
	}
}

void CPhoneNumbersView::RequestInsert()
{
	CPhoneNumbersInfo* pInfo = new CPhoneNumbersInfo();

	CDialogPhoneNumbers oDialog(pInfo, CCommonListView::DialogModeEdit);

	INT_PTR result = oDialog.DoModal();
	if (result == IDOK)
	{
		GetDocument()->DatabaseInsert(oDialog.m_recPhoneNumForUpdOrIns);
	}
}

void CPhoneNumbersView::RequestDelete()
{
	CPhoneNumbersDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);

	CString strMessage;

	strMessage.Format(_T("Are you sure you wish to delete this row\n\n"
		"- ID:   %s\n"
		"- Person ID:   %s\n"
		"- Phone type ID:   %s\n"
		"- Phone Number:   %s\n"
	),
		m_pListCtrl->GetItemText(m_SelectedIndex, 0),
		m_pListCtrl->GetItemText(m_SelectedIndex, 1),
		m_pListCtrl->GetItemText(m_SelectedIndex, 2),
		m_pListCtrl->GetItemText(m_SelectedIndex, 3)
	);


	int nResult = AfxMessageBox(strMessage, MB_YESNO);
	if (nResult == IDYES)
	{
		CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
		long nId = _ttol(strValue);

		oDocument->DatabaseDelete(nId);
	}
}

void CPhoneNumbersView::RequestUpdate()
{
	int nResult = AfxMessageBox(_T("Are you sure you wish to update this row?"), MB_YESNO);

	if (nResult == IDYES)
	{
		CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
		long nId = _ttol(strValue);

		if (nId > -1)
		{
			PHONE_NUMBERS recPhoneNum;

			CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 1);
			recPhoneNum.nPersonId = _ttoi(strValue);

			strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 2);
			recPhoneNum.nPhoneTypeId = _ttoi(strValue);

			wcscpy_s(recPhoneNum.szPhoneNumber, MAX_PHONE_NUMBER, m_pListCtrl->GetItemText(m_SelectedIndex, 3));


			CPhoneNumbersInfo* pInfo = new CPhoneNumbersInfo();
			pInfo->m_recPhoneNum = recPhoneNum;

			CDialogPhoneNumbers oDialog(pInfo, CCommonListView::DialogModeEdit);
			INT_PTR result = oDialog.DoModal();
			if (result == IDOK)
			{
				oDialog.m_recPhoneNumForUpdOrIns.nId = nId;
				GetDocument()->DatabaseUpdate(oDialog.m_recPhoneNumForUpdOrIns);
			}
		}
	}
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
		CreateListOnInit();
	}
}

void CPhoneNumbersView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListView::OnUpdate(pSender, lHint, pHint);
	m_pListCtrl = &GetListCtrl();

	CPhoneNumbersDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);


	if (lHint == SqlOperationInsert)
	{
		CGeneralHint<PHONE_NUMBERS>* pCitiesHint = dynamic_cast<CGeneralHint<PHONE_NUMBERS>*>(pHint);
		
		PHONE_NUMBERS recPhoneNum = pCitiesHint->m_recItem;

		CString strId;

		strId.Format(_T("%d"), recPhoneNum.nId);

		int index = m_pListCtrl->InsertItem(m_pListCtrl->GetItemCount(), strId);

		CString strPersonId;
		strPersonId.Format(_T("%d"), recPhoneNum.nPersonId);

		CString strPhoneTypeId;
		strPhoneTypeId.Format(_T("%d"), recPhoneNum.nPhoneTypeId);

		m_pListCtrl->SetItemText(index, 1, strPersonId);
		m_pListCtrl->SetItemText(index, 2, strPhoneTypeId);
		m_pListCtrl->SetItemText(index, 3, CString(recPhoneNum.szPhoneNumber));
	}
	else if (lHint == SqlOperationSelectById)
	{
		CGeneralHint<PHONE_NUMBERS>* phoneHint = dynamic_cast<CGeneralHint<PHONE_NUMBERS>*>(pHint);

		if (phoneHint->m_recItem.nId > -1)
		{
			m_pListCtrl->DeleteAllItems();
			InsertASingleRow(phoneHint->m_recItem);
		}
	}
	else if (lHint == SqlOperationSelectAll)
	{
		CSmartArray<PHONE_NUMBERS>* pCitiesHint = dynamic_cast<CSmartArray<PHONE_NUMBERS>*>(pHint);

		m_pListCtrl->DeleteAllItems();
		InsertCityRows(*pCitiesHint);
	}
	else if (lHint == SqlOperationUpdateById)
	{
		CGeneralHint<PHONE_NUMBERS>* pCitiesHint = dynamic_cast<CGeneralHint<PHONE_NUMBERS>*>(pHint);

		PHONE_NUMBERS recPhoneNum = pCitiesHint->m_recItem;

		CString strPersonId;
		strPersonId.Format(_T("%d"), recPhoneNum.nPersonId);

		CString strPhoneTypeId;
		strPhoneTypeId.Format(_T("%d"), recPhoneNum.nPhoneTypeId);

		m_pListCtrl->SetItemText(m_SelectedIndex, 1, strPersonId);
		m_pListCtrl->SetItemText(m_SelectedIndex, 2, strPhoneTypeId);
		m_pListCtrl->SetItemText(m_SelectedIndex, 3, CString(recPhoneNum.szPhoneNumber));

	}
	else if (lHint == SqlOperationDelete)
	{
		m_pListCtrl->DeleteItem(m_SelectedIndex);
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
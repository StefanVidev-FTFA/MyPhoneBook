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
#include "BaseDialog.h"

// Defines
// ----------------
IMPLEMENT_DYNCREATE(CPhoneNumbersView, CListView)
BEGIN_MESSAGE_MAP(CPhoneNumbersView, CListView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_INSERTROW, &CPhoneNumbersView::RequestInsert)
	ON_COMMAND(ID_EDIT_DELETEROW32774, &CPhoneNumbersView::RequestDelete)
	ON_COMMAND(ID_EDIT_SELECTBYID, &CPhoneNumbersView::RequestSelectById)
	ON_COMMAND(ID_EDIT_SELECTALL, &CPhoneNumbersView::RequestSelectAll)
	ON_COMMAND(ID_EDIT_UPDATEBYID, &CPhoneNumbersView::RequestUpdate)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneNumbersView::CPhoneNumbersView() noexcept {}
CPhoneNumbersView::~CPhoneNumbersView() {}

// Methods
// ----------------
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
void CPhoneNumbersView::InsertRows(CSmartArray<PHONE_NUMBERS>& oTableTypeArray,
	CMap<int, int, CString, const CString&>& personsMap,
	CMap<int, int, CString, const CString&>& phoneTypesMap
)
{
	for (INT_PTR i = 0; i < oTableTypeArray.GetCount(); ++i)
	{
		PHONE_NUMBERS* pRecItem = static_cast<PHONE_NUMBERS*>(oTableTypeArray.GetAt(i));

		if (pRecItem == nullptr)
			continue;

			CString strHolder;
			strHolder.Format(_T("%d"), pRecItem->nId);
			int row = static_cast<int>(m_pListCtrl->InsertItem(i, strHolder));

			m_pListCtrl->SetItemData(row, row);

			CString strPersonName;
			if (personsMap.Lookup(pRecItem->nPersonId, strPersonName))
				m_pListCtrl->SetItemText(row, 1, strPersonName);

			CString strPhoneType;
			if (phoneTypesMap.Lookup(pRecItem->nPhoneTypeId, strPhoneType))
				m_pListCtrl->SetItemText(row, 2, strPhoneType);

			m_pListCtrl->SetItemText(row, 3, CString(pRecItem->szPhoneNumber));

	}
	m_pListCtrl->SortItems(CUtils::CompareByName, (LPARAM)m_pListCtrl);
}

void CPhoneNumbersView::RequestSelectAll() {

	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to select all?"));

	int nResult = AfxMessageBox(strMessage, MB_YESNO);

	if (nResult == IDYES)
	{
		CPhoneNumbersDoc* oPhoneNumbersDocument = GetDocument();

		GetDocument()->SelectAll();
	}
}
void CPhoneNumbersView::RequestSelectById()
{
	CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
	long nId = _ttol(strValue);

	PHONE_NUMBERS recPhoneNumber;
	if (!GetDocument()->SelectById(nId, recPhoneNumber))
		return;

	CPhoneNumbersInfo* pInfo = new CPhoneNumbersInfo();

	pInfo->m_recPhoneNum = recPhoneNumber;

	CDialogPhoneNumbers oDialog(pInfo,DialogModeView);
	INT_PTR result = oDialog.DoModal();

	delete pInfo;

}
void CPhoneNumbersView::RequestInsert()
{
	CPhoneNumbersInfo* pInfo = new CPhoneNumbersInfo();

	CDialogPhoneNumbers oDialog(pInfo,DialogModeEdit);

	INT_PTR result = oDialog.DoModal();
	if (result == IDOK)
	{
		GetDocument()->Insert(oDialog.m_recPhoneNumForUpdOrIns);
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

		oDocument->Delete(nId);
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

			CDialogPhoneNumbers oDialog(pInfo, DialogModeEdit);
			INT_PTR result = oDialog.DoModal();
			if (result == IDOK)
			{
				oDialog.m_recPhoneNumForUpdOrIns.nId = nId;
				GetDocument()->Update(oDialog.m_recPhoneNumForUpdOrIns);
			}
		}
	}
}

// Overrides
// ----------------
BOOL CPhoneNumbersView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}
void CPhoneNumbersView::CreateListOnInit()
{
	CSmartArray<PHONE_NUMBERS>& oPhoneNumbersArray = GetDocument()->m_oInitialPhoneNumbersArray;

	SetViewStyle();

	DeclareColumns({ _T("ID"),_T("Owner Name"),_T("Phone Type"),_T("Phone number") });

	CMap<int, int, CString, const CString&> personsMap;
	CMap<int, int, CString, const CString&> phoneTypesMap;

	GetDocument()->AssignPersonsMap(personsMap);
	GetDocument()->AssignPhoneTypesMap(phoneTypesMap);

	InsertRows(oPhoneNumbersArray, personsMap, phoneTypesMap);
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


	if (lHint == ListViewHintTypesInsert)
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
	else if (lHint == ListViewHintTypesSelectAll)
	{
		CSmartArray<PHONE_NUMBERS>* pCitiesHint = dynamic_cast<CSmartArray<PHONE_NUMBERS>*>(pHint);

		m_pListCtrl->DeleteAllItems();

		CMap<int, int, CString, const CString&> personsMap;
		CMap<int, int, CString, const CString&> phoneTypesMap;

		GetDocument()->AssignPersonsMap(personsMap);
		GetDocument()->AssignPhoneTypesMap(phoneTypesMap);

		InsertRows(*pCitiesHint, personsMap, phoneTypesMap);
	}
	else if (lHint == ListViewHintTypesDelete)
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
void CPhoneNumbersView::OnLButtonDblClk(UINT /* nFlags */, CPoint point)
{
	CListCtrl& listCtrl = GetListCtrl();

	LVHITTESTINFO hitTestInfo = {};
	hitTestInfo.pt = point;

	int rowIndex = listCtrl.HitTest(&hitTestInfo);

	if (rowIndex != -1)
	{
		m_SelectedIndex = rowIndex;
		CPhoneNumbersView::RequestSelectById();
	}
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
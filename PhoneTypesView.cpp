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
#include "PhoneTypesView.h"
#include "PhoneTypes.h"
#include "PhoneTypesDoc.h"
#include "DialogPhoneTypes.h"


// Defines
// ----------------
IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)
BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_INSERTROW, &CPhoneTypesView::RequestInsert)
	ON_COMMAND(ID_EDIT_DELETEROW32774, &CPhoneTypesView::RequestDelete)
	ON_COMMAND(ID_EDIT_SELECTBYID, &CPhoneTypesView::RequestSelectById)
	ON_COMMAND(ID_EDIT_SELECTALL, &CPhoneTypesView::RequestSelectAll)
	ON_COMMAND(ID_EDIT_UPDATEBYID, &CPhoneTypesView::RequestUpdate)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneTypesView::CPhoneTypesView() noexcept {}
CPhoneTypesView::~CPhoneTypesView() {}

// Methods
// ----------------
void CPhoneTypesView::RequestSelectById()
{
	CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
	long nId = _ttol(strValue);

	PHONE_TYPES recPhoneType;

	if (!GetDocument()->SelectById(nId, recPhoneType))
		return;

	CDialogPhoneTypes oDialog(DialogModeView, CString(recPhoneType.szPhoneType));

	INT_PTR result = oDialog.DoModal();
}
void CPhoneTypesView::RequestSelectAll() {

	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to select all?"));

	int nResult = AfxMessageBox(strMessage, MB_YESNO);

	if (nResult == IDYES)
	{
		CPhoneTypesDoc* oPhoneTypesDocument = GetDocument();

		GetDocument()->SelectAll();
	}
}
void CPhoneTypesView::RequestInsert()
{
	CDialogPhoneTypes oInsertDlg(DialogModeEdit);

	INT_PTR result = oInsertDlg.DoModal();

	if (result == IDOK)
	{
		GetDocument()->Insert(oInsertDlg.m_recPhoneTypeForUpdOrIns);
	}
}
void CPhoneTypesView::RequestDelete()
{
	CPhoneTypesDoc* oPhoneTypesDocument = GetDocument();
	ASSERT_VALID(oPhoneTypesDocument);


	CString strMessage;

	strMessage.Format(_T("Are you sure you wish to delete this row\n\n"
		"- ID:   %s\n"
		"- Phone Type:   %s"
	),
		m_pListCtrl->GetItemText(m_SelectedIndex, 0),
		m_pListCtrl->GetItemText(m_SelectedIndex, 1)
	);


	int nResult = AfxMessageBox(strMessage, MB_YESNO);
	if (nResult == IDYES)
	{
		CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
		long nId = _ttol(strValue);

		oPhoneTypesDocument->Delete(nId);
	}
}
void CPhoneTypesView::RequestUpdate()
{
	int nResult = AfxMessageBox(_T("Are you sure you wish to update this row?"), MB_YESNO);

	if (nResult == IDYES)
	{
		CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
		long nId = _ttol(strValue); 

		if (nId > -1)
		{
			CString strCurrentNumber = m_pListCtrl->GetItemText(m_SelectedIndex, 1);

			CDialogPhoneTypes oDialog(DialogModeEdit, strCurrentNumber);

			INT_PTR result = oDialog.DoModal();

			if (result == IDOK)
			{
				PHONE_TYPES recItemforUpdate = oDialog.m_recPhoneTypeForUpdOrIns;
				recItemforUpdate.nId = nId;

				GetDocument()->Update(recItemforUpdate);
			}
		}
	}
}

void CPhoneTypesView::InsertRows(CSmartArray<PHONE_TYPES>& oPhoneTypesArray)
{
	for (INT_PTR i = 0; i < oPhoneTypesArray.GetCount(); ++i)
	{
		PHONE_TYPES* pRecItem = static_cast<PHONE_TYPES*>(oPhoneTypesArray.GetAt(i));

		if (pRecItem == nullptr)
			continue;

			CString strHolder;

			strHolder.Format(_T("%d"), pRecItem->nId);
			int row = static_cast<int>(m_pListCtrl->InsertItem(i, strHolder));

			m_pListCtrl->SetItemText(i, 1, CString(pRecItem->szPhoneType));

	}
}

// Overrides
// ----------------
BOOL CPhoneTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}
void CPhoneTypesView::CreateListOnInit()
{
	CSmartArray<PHONE_TYPES>& oPhoneTypesArray = GetDocument()->m_oInitialPhoneTypesArray;

	SetViewStyle();

	DeclareColumns({ _T("ID"),_T("Phone type") });

	InsertRows(oPhoneTypesArray);
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
void CPhoneTypesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListView::OnUpdate(pSender, lHint, pHint);
	m_pListCtrl = &GetListCtrl();

	CPhoneTypesDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);


	if (lHint == ListViewHintTypesInsert)
	{
		CGeneralHint<PHONE_TYPES>* pPhoneTypesHint = dynamic_cast<CGeneralHint<PHONE_TYPES>*>(pHint);

		PHONE_TYPES recPhoneType = pPhoneTypesHint->m_recItem;

		CString strId;

		strId.Format(_T("%d"), recPhoneType.nId);

		int index = m_pListCtrl->InsertItem(m_pListCtrl->GetItemCount(), strId);

		m_pListCtrl->SetItemText(index, 1, CString(recPhoneType.szPhoneType));

	}
	else if (lHint == ListViewHintTypesSelectById)
	{
	}
	else if (lHint == ListViewHintTypesSelectAll)
	{
		CSmartArray<PHONE_TYPES>* pPhoneTypesHint = dynamic_cast<CSmartArray<PHONE_TYPES>*>(pHint);

		m_pListCtrl->DeleteAllItems();
		InsertRows(*pPhoneTypesHint);
	}
	else if (lHint == ListViewHintTypesUpdateById)
	{
		CGeneralHint<PHONE_TYPES>* pPhoneTypesHint = dynamic_cast<CGeneralHint<PHONE_TYPES>*>(pHint);

		PHONE_TYPES recPhoneType = pPhoneTypesHint->m_recItem;

		m_pListCtrl->SetItemText(m_SelectedIndex, 1, CString(recPhoneType.szPhoneType));

	}
	else if (lHint == ListViewHintTypesDelete)
	{
		m_pListCtrl->DeleteItem(m_SelectedIndex);
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
void CPhoneTypesView::OnLButtonDblClk(UINT /* nFlags */, CPoint point)
{
	CListCtrl& listCtrl = GetListCtrl();

	LVHITTESTINFO hitTestInfo = {};
	hitTestInfo.pt = point;

	int rowIndex = listCtrl.HitTest(&hitTestInfo);

	if (rowIndex != -1)
	{
		m_SelectedIndex = rowIndex;
		CPhoneTypesView::RequestSelectById();
	}
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
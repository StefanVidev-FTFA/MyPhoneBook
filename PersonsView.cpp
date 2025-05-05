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
#include "DialogPersons.h"

// Defines
// ----------------
IMPLEMENT_DYNCREATE(CPersonsView, CListView)
BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_SELECTALL, &CPersonsView::RequestSelectAll)
	ON_COMMAND(ID_EDIT_INSERTROW, &CPersonsView::RequestInsert)
	ON_COMMAND(ID_EDIT_DELETEROW32774, &CPersonsView::RequestDelete)
	ON_COMMAND(ID_EDIT_UPDATEBYID, &CPersonsView::RequestUpdate)
	ON_COMMAND(ID_EDIT_SELECTBYID, &CPersonsView::RequestSelectById)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsView::CPersonsView() noexcept {}
CPersonsView::~CPersonsView() {}

// Methods
// ----------------
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
	PERSONS recPerson;
	AssignPerson(recPerson);

	CSmartArray<CITIES> oCitiesArray;
	CSmartArray<PHONE_NUMBERS> oPhoneNumbersArray;
	CCitiesTable oCitiesTable;

	oCitiesTable.SelectAll(oCitiesArray);


	CDialogPersons oDialog(oCitiesArray, oPhoneNumbersArray, recPerson);

	INT_PTR result = oDialog.DoModal();

	if (result == IDOK)
	{
		GetDocument()->DatabaseInsert(oDialog.m_recPersonToInsert, oPhoneNumbersArray);
	}
}
void CPersonsView::RequestDelete()
{
	CPersonsDoc* oDocument = GetDocument();
	ASSERT_VALID(oDocument);

	CString strMessage;
	strMessage.Format(_T("Are you sure you wish to delete this row\n\n"
		"- ID:   %s\n"
		"- First Name:   %s\n"
		"- Last Name:   %s\n"
		"- EGN:   %s\n"
	),
		m_pListCtrl->GetItemText(m_SelectedIndex, 0),
		m_pListCtrl->GetItemText(m_SelectedIndex, 1),
		m_pListCtrl->GetItemText(m_SelectedIndex, 3),
		m_pListCtrl->GetItemText(m_SelectedIndex, 4)
	);
	int nResult = AfxMessageBox(strMessage, MB_YESNO);
	if (nResult == IDYES)
	{
		CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
		long nId = _ttol(strValue);
		oDocument->DatabaseDelete(nId);
	}
}
void CPersonsView::AssignPerson(PERSONS& recItem)
{
	CListCtrl* oListCtrl = &GetListCtrl();

	// Enum za list control columns
	recItem.nId = _ttoi(m_pListCtrl->GetItemText(m_SelectedIndex, 0));
	wcscpy_s(recItem.szFirstName, MAX_ANY_NAME, m_pListCtrl->GetItemText(m_SelectedIndex, 1));
	wcscpy_s(recItem.szMiddleName, MAX_ANY_NAME, m_pListCtrl->GetItemText(m_SelectedIndex, 2));
	wcscpy_s(recItem.szLastName, MAX_ANY_NAME, m_pListCtrl->GetItemText(m_SelectedIndex, 3));
	wcscpy_s(recItem.szEgn, MAX_EGN, m_pListCtrl->GetItemText(m_SelectedIndex, 4));
	wcscpy_s(recItem.szAddress, MAX_ADRESS, m_pListCtrl->GetItemText(m_SelectedIndex, 6));
	recItem.nCityId = _ttoi(m_pListCtrl->GetItemText(m_SelectedIndex, 5));

}
void CPersonsView::RequestUpdate()
{
	int nResult = AfxMessageBox(_T("Are you sure you wish to update this row?"), MB_YESNO);

	if (nResult == IDYES)
	{
		CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
		long nId = _ttol(strValue);

		if (nId > -1)
		{
			CListCtrl* oListCtrl = &GetListCtrl();

			const long lSelectedItemIndex = oListCtrl->GetSelectionMark();
			if (lSelectedItemIndex <= 0)
				return;

			//const long lPersonID = oListCtrl->GetItemData(lSelectedItemIndex);

			const long lPersonID = nId;

			//Utils::MessageWithLong(_T("The person id is: %ld"), lPersonID);

			PERSONS recPerson;
			CPersonsTable oPersonsTable;
			if (!oPersonsTable.SelectWhereID(lPersonID, recPerson))
				return;

			// Това трябва да се зарежда в документа и да се взима от там
			CSmartArray<PHONE_NUMBERS> oPersonsPhoneNumbersArray;
			CPhoneNumbersTable oPhonenumbersTable;
			if (!oPhonenumbersTable.GetPersonsPhoneNumbers(oPersonsPhoneNumbersArray, recPerson.nId))
				return;


			CDialogPersons oDialog(GetDocument()->m_oCitiesArray,
				oPersonsPhoneNumbersArray,
				recPerson,
				false,
				true);


			INT_PTR result = oDialog.DoModal();


			if (result == IDOK)
			{
				oDialog.m_recPersonToInsert.nId = lPersonID;
				GetDocument()->DatabaseUpdate(oDialog.m_recPersonToInsert, oPersonsPhoneNumbersArray);
			}
		}
	}
}
void CPersonsView::RequestSelectById()
{
	CString strValue = m_pListCtrl->GetItemText(m_SelectedIndex, 0);
	long nId = _ttol(strValue);

	PERSONS recPerson;

	if (!GetDocument()->DatabaseSelectById(nId, recPerson))
		return;

	CSmartArray<CITIES> oCitiesArray;
	CCitiesTable oCitiesTable;
	oCitiesTable.SelectAll(oCitiesArray);

	CSmartArray<PHONE_NUMBERS> oPersonsPhoneNumbersArray;
	CPhoneNumbersTable oPhonenumbersTable;
	oPhonenumbersTable.GetPersonsPhoneNumbers(oPersonsPhoneNumbersArray, recPerson.nId);


	CDialogPersons oDialog(oCitiesArray, oPersonsPhoneNumbersArray, recPerson,true,true);

	INT_PTR result = oDialog.DoModal();
}

// Overrides
// ----------------
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

	InsertPersonRows(oPersonsArray);
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


	if (lHint == ListViewHintTypesInsert)
	{
		CGeneralHint<PERSONS>* pPersonsHint = dynamic_cast<CGeneralHint<PERSONS>*>(pHint);
		PERSONS recPerson = pPersonsHint->m_recItem;
		CString strId;
		strId.Format(_T("%d"), recPerson.nId);
		int index = m_pListCtrl->InsertItem(m_pListCtrl->GetItemCount(), strId);
		CString strFirstName;
		strFirstName.Format(_T("%s"), recPerson.szFirstName);
		CString strMiddleName;
		strMiddleName.Format(_T("%s"), recPerson.szMiddleName);
		CString strLastName;
		strLastName.Format(_T("%s"), recPerson.szLastName);
		CString strEgn;
		strEgn.Format(_T("%s"), recPerson.szEgn);
		CString strCityId;
		strCityId.Format(_T("%d"), recPerson.nCityId);
		CString strAddress;
		strAddress.Format(_T("%s"), recPerson.szAddress);

		m_pListCtrl->SetItemText(index, 1, strFirstName);
		m_pListCtrl->SetItemText(index, 2, strMiddleName);
		m_pListCtrl->SetItemText(index, 3, strLastName);
		m_pListCtrl->SetItemText(index, 4, strEgn);
		m_pListCtrl->SetItemText(index, 5, strCityId);
		m_pListCtrl->SetItemText(index, 6, strAddress);
	}
	else if (lHint == ListViewHintTypesSelectAll)
	{
		CSmartArray<PERSONS>* pPersonsHint = dynamic_cast<CSmartArray<PERSONS>*>(pHint);

		m_pListCtrl->DeleteAllItems();
		InsertPersonRows(*pPersonsHint);
	}
	else if (lHint == ListViewHintTypesUpdateById)
	{
		CGeneralHint<PERSONS>* pPersonsHint = dynamic_cast<CGeneralHint<PERSONS>*>(pHint);
		PERSONS recPerson = pPersonsHint->m_recItem;
		CString strId;
		strId.Format(_T("%d"), recPerson.nId);
		m_pListCtrl->SetItemText(m_SelectedIndex, 0, strId);
		m_pListCtrl->SetItemText(m_SelectedIndex, 1, CString(pPersonsHint->m_recItem.szFirstName));
		m_pListCtrl->SetItemText(m_SelectedIndex, 2, CString(pPersonsHint->m_recItem.szMiddleName));
		m_pListCtrl->SetItemText(m_SelectedIndex, 3, CString(pPersonsHint->m_recItem.szLastName));
		m_pListCtrl->SetItemText(m_SelectedIndex, 4, CString(pPersonsHint->m_recItem.szEgn));

		strId.Format(_T("%d"), pPersonsHint->m_recItem.nCityId);
		m_pListCtrl->SetItemText(m_SelectedIndex, 5, strId);
		m_pListCtrl->SetItemText(m_SelectedIndex, 6, CString(pPersonsHint->m_recItem.szAddress));
	}
	else if (lHint == ListViewHintTypesDelete)
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
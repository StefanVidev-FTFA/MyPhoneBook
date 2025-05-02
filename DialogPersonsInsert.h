#pragma once
#include "afxdialogex.h"
#include <vector>
#include "Persons.h"
#include "PhoneNumbers.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDialogPersonsInsert
class CDialogPersonsInsert : public CDialogEx
{
	// Constants
	// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DEFINE };
#endif

	// Constructor / Destructor
	// ----------------
public:
	DECLARE_DYNAMIC(CDialogPersonsInsert)
	CDialogPersonsInsert(const CSmartArray<CITIES>& cityIds,
		CSmartArray<PHONE_NUMBERS>& phoneNumbers,PERSONS recPersonView,
		bool isReadOnly=false,bool fillOut=false, CWnd* pParent = nullptr);
	virtual ~CDialogPersonsInsert();

	// Methods
	// ----------------
public:
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();
	afx_msg void OnNMRClickListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void InsertPhoneNumber();
	afx_msg void EditPhoneNumber();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	void FillPhones();
	DECLARE_MESSAGE_MAP()

	// Members
	// ----------------
public:
	CEdit m_EditBoxFirstName;
	CEdit m_EditBoxMiddleName;
	CEdit m_EditBoxLastName;
	CEdit m_EditBoxEgn;
	CEdit m_EditBoxAdress;

	CComboBox m_ComboBoxCityId;
	PERSONS m_recPersonToInsert;

	CButton m_ButtonPersonsConfirm;
	CListCtrl m_ListControlPhoneNumbers;
private :
	PERSONS m_recPersonToFillOut;
	const CSmartArray<CITIES>& m_oCitiesArray;
	CSmartArray<PHONE_NUMBERS>& m_oPhoneNumbersArray;

	bool m_isReadOnly;
	bool m_fillOut;
};

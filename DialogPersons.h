#pragma once
#include "afxdialogex.h"
#include <vector>
#include "Persons.h"
#include "PhoneNumbers.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogPersonsInsert
class CDialogPersons : public CDialogEx
{
// Constants
// ----------------
	enum { IDD = IDD_PERSONS_DEFINE };

// Defines
// ----------------
	DECLARE_DYNAMIC(CDialogPersons)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
public:
	// Да добавя dialogMode enum-a.
	CDialogPersons(const CSmartArray<CITIES>& oCitiesArray,
		CSmartArray<PHONE_NUMBERS>& phoneNumbers,
		PERSONS recPerson,
		bool isReadOnly=false,
		bool fillOut=false, 
		CWnd* pParent = nullptr);

	virtual ~CDialogPersons();

// Methods
// ----------------
public:
	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();
	afx_msg void OnNMRClickListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void InsertPhoneNumber();
	afx_msg void EditPhoneNumber();
	afx_msg void RemovePhoneNumber();

protected:
	void FillPhones();

// Overrides
// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

// Members
// ----------------
public:
	CEdit m_EditBoxFirstName;
	CEdit m_EditBoxMiddleName;
	CEdit m_EditBoxLastName;
	CEdit m_EditBoxEgn;
	// m_edbAddress
	CEdit m_EditBoxAdress;

	CComboBox m_cmbCities;
	PERSONS m_recPersonToInsert;

	CButton m_ButtonPersonsConfirm;
	// m_btnButtonPersonsConfirm

	CListCtrl m_ListControlPhoneNumbers;

private:
	PERSONS m_recPersonToFillOut;
	const CSmartArray<CITIES>& m_oCitiesArray;
	CSmartArray<PHONE_NUMBERS>& m_oPhoneNumbersArray;

	bool m_isReadOnly;
	bool m_fillOut;
};

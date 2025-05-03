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
		bool bIsReadOnly=false,
		bool bFillOut=false, 
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
	CEdit m_edbFirstName;
	CEdit m_edbMiddleName;
	CEdit m_edbLastName;
	CEdit m_edbEgn;
	CEdit m_edbAddress;

	CComboBox m_cmbCities;
	PERSONS m_recPersonToInsert;
	CButton m_btnPersonsConfirm;
	CListCtrl m_lscPhoneNumbers;

private:
	PERSONS m_recPersonToFillOut;
	CSmartArray<PHONE_NUMBERS>& m_oPhoneNumbersArray;

	const CSmartArray<CITIES>& m_oCitiesArray;
	bool m_bIsReadOnly;
	bool m_bFillOut;
};

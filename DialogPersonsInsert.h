#pragma once
#include "afxdialogex.h"
#include <vector>
#include "Persons.h"
#include "PhoneNumbers.h"


using namespace std;

class DialogPersonsInsert : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPersonsInsert)

public:
	DialogPersonsInsert(const CSmartArray<CITIES>& cityIds,
		CSmartArray<PHONE_NUMBERS>& phoneNumbers,PERSONS recPersonView,
		bool isReadOnly=false, CWnd* pParent = nullptr);

	virtual ~DialogPersonsInsert();

	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();
	afx_msg void OnNMRClickListControl(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void InsertPhoneNumber();
	afx_msg void EditPhoneNumber();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DEFINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void FillPhones();
	DECLARE_MESSAGE_MAP()

public:
	CEdit m_EditBoxFirstName;
	CEdit m_EditBoxMiddleName;
	CEdit m_EditBoxLastName;
	CEdit m_EditBoxEgn;
	CEdit m_EditBoxAdress;
	CComboBox m_ComboBoxCityId;

	PERSONS m_recPersonToInsert;
private :
	PERSONS m_recPersonToFillOut;
	const CSmartArray<CITIES>& m_oCitiesArray;
	CSmartArray<PHONE_NUMBERS>& m_oPhoneNumbersArray;
	bool m_isReadOnly;
public:
	CButton m_ButtonPersonsConfirm;
	CListCtrl m_ListControlPhoneNumbers;
};

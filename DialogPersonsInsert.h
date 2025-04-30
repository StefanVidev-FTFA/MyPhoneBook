#pragma once
#include "afxdialogex.h"
#include <vector>
#include "Persons.h"


using namespace std;

class DialogPersonsInsert : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPersonsInsert)

public:
	DialogPersonsInsert(const CStringList& cityIds, CWnd* pParent = nullptr);
	DialogPersonsInsert(const CStringList& cityIds,PERSONS recPersonView, CWnd* pParent = nullptr);
	virtual ~DialogPersonsInsert();

	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();
	afx_msg void OnNMRClickListControl(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnListOption1();
	afx_msg void OnListOption2();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DEFINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
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
	const CStringList& m_cityIds;
};

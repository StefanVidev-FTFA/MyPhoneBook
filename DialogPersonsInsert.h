#pragma once
#include "afxdialogex.h"
#include <vector>


using namespace std;

class DialogPersonsInsert : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPersonsInsert)

public:
	DialogPersonsInsert(const CStringList& cityIds, CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogPersonsInsert();

	afx_msg void OnClickedButtonConfirm();
	afx_msg void OnClickedButtonCancel();


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
private :
	const CStringList& m_cityIds;
};

#include <atldbcli.h>
#include <iostream>

using namespace std;

#define COMPANY_NAME_SIZE	32
#define NAME_SIZE			32
#define ADDRESS_SIZE		64
#define COUNTRY_SIZE		8

/// <summary>�������� ��������� �� ����� �� ������� CUSTOMERS</summary>
struct CUSTOMERS
{
	/// <summary>�������� ������������� �� ���</summary>
	long lID;
	/// <summary>Versioning</summary>
	long lUpdateCounter;
	/// <summary>������������ �� �������</summary>
	TCHAR szCompanyName[COMPANY_NAME_SIZE];
	/// <summary>����� �� ������������ �� �������</summary>
	TCHAR szName[NAME_SIZE];
	/// <summary>����� �� �������</summary>
	TCHAR szAddress[ADDRESS_SIZE];
	/// <summary>������ �� ISO ���</summary>
	TCHAR szCountry[COUNTRY_SIZE];

	CUSTOMERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CCustomersAccessor
{
protected:
	CUSTOMER m_recCustomer;

	BEGIN_ACCESSOR_MAP(CCustomersAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recCustomer.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recCustomer.lUpdateCounter)
		COLUMN_ENTRY(3, m_recCustomer.szCompanyName)
		COLUMN_ENTRY(4, m_recCustomer.szName)
		COLUMN_ENTRY(5, m_recCustomer.szAddress)
		COLUMN_ENTRY(6, m_recCustomer.szCountry)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/// <summary>���� �� ������ � ������� CUSTOMERS</summary>
class CCustomersTable : private CCommand<CAccessor<CCustomersAccessor>>
{
public:
	BOOL LoadCustomers();
	BOOL UpdateCustomer();
};

BOOL CCustomersTable::LoadCustomers()
{
	CDataSource oDataSource; // ������ � ��
	CSession oSession; // �����

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("SQLSERVER"));	// ������
	oDBPropSet.AddProperty(DBPROP_AUTH_USERID, _T("sa"));			// ����������
	oDBPropSet.AddProperty(DBPROP_AUTH_PASSWORD, _T("sa"));			// ������ // windows authentication
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("Northwind"));	// ���� �����
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// ��������� �� ��� ������ �����
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		Message(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// �������� �����
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		Message(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	// ������������ ��������
	CString strQuery = _T("SELECT * FROM CUSTOMERS");

	// ����������� ���������
	hResult = Open(oSession, strQuery);
	if (FAILED(hResult))
	{
		Message(_T("Error executing query. Error: %d. Query: %s"), hResult, strQuery);

		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	// ��������� ������ �����
	while (MoveNext() == S_OK)
	{
		CString strCustomerData;
		strCustomerData.Format(_T("ID: %d, Company: %s, Contact Name: %s"),
			m_recCustomer.m_lID,
			m_recCustomer.m_szCompanyName,
			m_recCustomer.m_szName);

		// Logic with the result

		// DB_S_ENDOFROWSET
	}

	// ��������� ���������, ������� � �������� � ������ �����. 
	Close();
	oSession.Close();
	oDataSource.Close();

	return TRUE;
}

BOOL CCustomersTable::UpdateCustomer()
{
	CDataSource oDataSource;
	CSession oSession;

	CDBPropSet oDBPropSet(DBPROPSET_oDBPropSet);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("SQLSERVER"));	// ������
	oDBPropSet.AddProperty(DBPROP_AUTH_USERID, _T("sa"));			// ����������
	oDBPropSet.AddProperty(DBPROP_AUTH_PASSWORD, _T("sa"));			// ������
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("Northwind"));	// ���� �����
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// ��������� �� ��� ������ �����
	hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		Message(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// 1) lock

	// �������� �����
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		Message(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	// 1) lock

	// ������������ ��������
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CUSTOMERS WITH(...) WHERE ID = %d"), 1);

	// ��������� �� ���� �� Rowset-�
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

	// ����������� ���������
	hResult = Open(oSession, strQuery, oUpdateDBPropSet);
	if (FAILED(hResult))
	{
		Message(_T("Error executing query. Error: %d. Query: %s"), hResult, strQuery);

		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		Message(_T("Error opening record. Error: %d. Query: %s"), hResult, strQuery);

		Close();
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	// ������: ����� ������ ������ �� �������� ����� �� �������������� m_lUpdateCounter?
	// 2) check Update counter value != update counter from db

	m_recCustomer.m_lUpdateCounter++; // DB

	hResult = SetData(1);
	if (FAILED(hResult))
	{
		Message(_T("Error updating record. Error: %d. Query: %s"), hResult, strQuery);

		Close();
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	Close();
	oSession.Close();
	oDataSource.Close();

	return TRUE;
}
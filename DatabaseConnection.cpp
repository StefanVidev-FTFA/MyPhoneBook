#include "pch.h"
#include "DatabaseConnection.h"
#include <atldbcli.h>
#include <afxwin.h>

#define SERVER_NAME _T("DESKTOP-8T6EC12")
#define DATABASE_NAME _T("PHONEBOOK")
#define MICROSOFT_AUTHENTICATION_ARGUMENT _T("SSPI")

/////////////////////////////////////////////////////////////////////////////
// CDatabaseConnection


// Constructor / Destructor
// ----------------
CDatabaseConnection::CDatabaseConnection()
	: m_oDBDatabaseConnectionPropertiesSet(DBPROPSET_DBINIT),
    m_oDBDatabaseRowsetPropertiesSet(DBPROPSET_ROWSET)
{
    m_oDBDatabaseConnectionPropertiesSet.AddProperty(DBPROP_AUTH_INTEGRATED, MICROSOFT_AUTHENTICATION_ARGUMENT);
    m_oDBDatabaseConnectionPropertiesSet.AddProperty(DBPROP_INIT_DATASOURCE, SERVER_NAME);
    m_oDBDatabaseConnectionPropertiesSet.AddProperty(DBPROP_INIT_CATALOG, DATABASE_NAME);


    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_IRowsetChange, true);
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_IRowsetUpdate, true);
}
CDatabaseConnection::~CDatabaseConnection(){}



// Methods
// ----------------


CDatabaseConnection& CDatabaseConnection::GetInstance()
{
    static CDatabaseConnection instance;
    return instance;
}
void CDatabaseConnection::Connect()
{


    // Свързваме се към базата данни
    HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB.1"), &m_oDBDatabaseConnectionPropertiesSet);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
        AfxMessageBox(strError);
    }
    else 
    {
        AfxMessageBox(_T("Successfully connected to the SQL Server database"), MB_ICONINFORMATION);
    }
}
void CDatabaseConnection::Disconnect()
{
    // Затваряме сесията и връзката с базата данни. 
    Close();
    m_oDataSource.Close();
    AfxMessageBox(_T("Database Disconnected!"), MB_ICONINFORMATION);
}

// Overrides
// ----------------
    
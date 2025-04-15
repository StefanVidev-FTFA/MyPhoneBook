#include "pch.h"
#include "DatabaseConnection.h"
#include <atldbcli.h>
#include <afxwin.h>
#include "Macros.h"

#define SERVER_NAME _T("DESKTOP-8T6EC12")
#define DATABASE_NAME _T("PHONEBOOK")
#define MICROSOFT_AUTHENTICATION_ARGUMENT _T("SSPI")

/////////////////////////////////////////////////////////////////////////////
// CDatabaseConnection
// 
    // Constructor / Destructor
    // ----------------
CDatabaseConnection::CDatabaseConnection()
	: m_oDBDatabaseConnectionPropertiesSet(DBPROPSET_DBINIT),
    m_oDBDatabaseRowsetPropertiesSet(DBPROPSET_ROWSET)
{
    m_oDBDatabaseConnectionPropertiesSet.AddProperty(DBPROP_AUTH_INTEGRATED, MICROSOFT_AUTHENTICATION_ARGUMENT);
    m_oDBDatabaseConnectionPropertiesSet.AddProperty(DBPROP_INIT_DATASOURCE, SERVER_NAME);
    m_oDBDatabaseConnectionPropertiesSet.AddProperty(DBPROP_INIT_CATALOG, DATABASE_NAME);


    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_INIT_LCID, 1033L);
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_IRowsetChange, true);
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_IRowsetScroll, true);
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

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
        MESSAGE_ERROR(strError);
    }
    else 
    {
        MESSAGE_INFO(_T("Successfully connected to the SQL Server database"));
    }
}
void CDatabaseConnection::Disconnect()
{
    Close();
    m_oDataSource.Close();
    MESSAGE_INFO(_T("Database Disconnected!"));
}
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

    // Constructor / Destructor
    // ----------------
CDatabaseConnection::CDatabaseConnection()
	: m_oDBDatabaseConnectionPropertiesSet(DBPROPSET_DBINIT),
    m_oDBDatabaseRowsetPropertiesSet(DBPROPSET_ROWSET), m_propsInitialized(false)
{
}
CDatabaseConnection::~CDatabaseConnection(){}

    // Methods
    // ----------------
void CDatabaseConnection::InitializeConnectionProperties()
{
    m_oDBDatabaseConnectionPropertiesSet = CDBPropSet(DBPROPSET_DBINIT);
    m_oDBDatabaseConnectionPropertiesSet.AddProperty(DBPROP_AUTH_INTEGRATED, MICROSOFT_AUTHENTICATION_ARGUMENT);
    m_oDBDatabaseConnectionPropertiesSet.AddProperty(DBPROP_INIT_DATASOURCE, SERVER_NAME);
    m_oDBDatabaseConnectionPropertiesSet.AddProperty(DBPROP_INIT_CATALOG, DATABASE_NAME);
}

void CDatabaseConnection::InitializeRowsetProperties()
{
    m_oDBDatabaseRowsetPropertiesSet = CDBPropSet(DBPROPSET_ROWSET);
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_INIT_LCID, 1033L);
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_IRowsetChange, true);
    m_oDBDatabaseRowsetPropertiesSet.AddProperty(DBPROP_IRowsetScroll, true);
}

CDatabaseConnection& CDatabaseConnection::GetInstance()
{
    static CDatabaseConnection instance;
    return instance;
}

void CDatabaseConnection::Connect()
{
    if (!m_propsInitialized)
    {
        InitializeConnectionProperties();
        InitializeRowsetProperties();
        m_propsInitialized = true;
    }

    HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB.1"), &m_oDBDatabaseConnectionPropertiesSet);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
        MESSAGE_ERROR(strError);
    }
}

bool CDatabaseConnection::OpenSession()
{
    if (m_sessionIsOpen)
    {
        return true;
    }

    HRESULT  hResult = m_oCurrentSession.Open(m_oDataSource);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Unable to open session.Error: %ld"), hResult);
        AfxMessageBox(strError);

        return false;
    }

    m_sessionIsOpen = true;
    return true;
}
bool CDatabaseConnection::CloseSession()
{
    if (!m_sessionIsOpen)
    {
        return true;
    }
    m_oCurrentSession.Close();
    return true;
}

void CDatabaseConnection::Disconnect()
{
    if (m_sessionIsOpen)
    {
        m_oCurrentSession.Close();
    }
    m_oDataSource.Close();
}
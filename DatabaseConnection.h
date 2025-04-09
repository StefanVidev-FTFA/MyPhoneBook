#pragma once
#include "pch.h"
#include "CitiesTable.h"
#include <iostream>
#include <atldbcli.h>
#include "CitiesArray.h"
#include <afxwin.h>
#include <oledb.h>


/////////////////////////////////////////////////////////////////////////////
// CDatabaseConnection

/// <summary>
/// Singleton class dedicated to establishing the connection with the database.
/// As well as breaking that connection and also holds differnt CDB property sets,
/// for executing different commands on the database.
/// </summary>
class CDatabaseConnection : private CCommand<CAccessor<CCitiesAccessor>>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
private:

    /// <summary>Constructor for the DatabaseConnection in which the 
    /// different CDB property sets are being defined
    /// </summary>
    CDatabaseConnection();
    ~CDatabaseConnection();

// Methods
// ----------------
public:
    /// <summary> Returns the instance of the singleton class </summary>
    static CDatabaseConnection& GetInstance();
    /// <summary>Use to connect to the database (should be called once at InitInstance()) </summary>
    void Connect();
    /// <summary>Disconnects from the database, recommended to be called at ExitInstance() </summary>
    void Disconnect();
    /// <summary>Returns a property set which holds the properties for UPDATE, INSERT and DELETE </summary>
	CDBPropSet GetRowsetPropertiesSet() { return m_oDBDatabaseRowsetPropertiesSet; }
    /// <summary>Returns the data source</summary>
	CDataSource& GetDataSource() { return m_oDataSource; }


// Overrides
// ----------------


// Members
// ----------------
private:

    CDBPropSet m_oDBDatabaseConnectionPropertiesSet;
    CDBPropSet m_oDBDatabaseRowsetPropertiesSet;
    CDataSource m_oDataSource;



    CDatabaseConnection(const CDatabaseConnection&) = delete;
    CDatabaseConnection& operator=(const CDatabaseConnection&) = delete;
};

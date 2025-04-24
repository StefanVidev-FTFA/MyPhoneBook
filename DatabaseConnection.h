#pragma once
#include "pch.h"
#include <iostream>
#include <atldbcli.h>
#include "CitiesArray.h"
#include <afxwin.h>
#include <oledb.h>


/////////////////////////////////////////////////////////////////////////////
// CDatabaseConnection

/// <summary>
///Сингълтън клас, предназначен за установяване на връзка с базата данни.
///Също така отговаря за прекъсването на тази връзка и съдържа различни CDB property sets,
///използвани за изпълнение на различни команди върху базата данни.
/// </summary>
class CDatabaseConnection
{
// Constructor / Destructor
// ----------------
private:
    CDatabaseConnection();
    ~CDatabaseConnection();

// Methods
// ----------------
public:
    /// <summary> Връща instance на класът </summary>
    static CDatabaseConnection& GetInstance();
    /// <summary> Установява връзка със базата данни </summary>
    void Connect();
    /// <summary> Затваря връзката със базата данни </summary>
    void Disconnect();
    /// <summary> Връща настройки за UPDATE, INSERT and DELETE функциите </summary>
	CDBPropSet GetRowsetPropertiesSet() { return m_oDBDatabaseRowsetPropertiesSet; }
    /// <summary>Връща data source обект</summary>
	CDataSource& GetDataSource() { return m_oDataSource; }
private:
    /// <summary> Дефинира настройките за връзка </summary>
    void InitializeConnectionProperties();
    /// <summary> Дефинира настройките за UPDATE, INSERT и DELETE функциите </summary>
    void InitializeRowsetProperties();

// Members
// ----------------
private:

    CDBPropSet m_oDBDatabaseConnectionPropertiesSet;
    CDBPropSet m_oDBDatabaseRowsetPropertiesSet;
    CDataSource m_oDataSource;
    bool m_propsInitialized = false;

    CDatabaseConnection(const CDatabaseConnection&) = delete;
    CDatabaseConnection& operator=(const CDatabaseConnection&) = delete;
};

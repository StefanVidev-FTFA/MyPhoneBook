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
///��������� ����, ������������ �� ������������ �� ������ � ������ �����.
///���� ���� �������� �� ������������ �� ���� ������ � ������� �������� CDB property sets,
///���������� �� ���������� �� �������� ������� ����� ������ �����.
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
    /// <summary> ����� instance �� ������ </summary>
    static CDatabaseConnection& GetInstance();
    /// <summary> ���������� ������ ��� ������ ����� </summary>
    void Connect();
    /// <summary> ������� �������� ��� ������ ����� </summary>
    void Disconnect();
    /// <summary> ����� ��������� �� UPDATE, INSERT and DELETE ��������� </summary>
	CDBPropSet GetRowsetPropertiesSet() { return m_oDBDatabaseRowsetPropertiesSet; }
    /// <summary>����� data source �����</summary>
	CDataSource& GetDataSource() { return m_oDataSource; }
private:
    /// <summary> �������� ����������� �� ������ </summary>
    void InitializeConnectionProperties();
    /// <summary> �������� ����������� �� UPDATE, INSERT � DELETE ��������� </summary>
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

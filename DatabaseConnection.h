#pragma once
#include "pch.h"
#include <iostream>
#include <atldbcli.h>
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

    /// <summary> ������ ���� ����� </summary>
    bool OpenSession();
    /// <summary> ������� ������� </summary>
    bool CloseSession();
    /// <summary> ���������� ������ ��� ������ ����� </summary>
    void Connect();
    /// <summary> ������� �������� ��� ������ ����� </summary>
    void Disconnect();

    /// <summary> ����� reference ��� �������� ����� </summary>
    CSession& GetCurrentSession() { return m_oCurrentSession; }
    /// <summary> ����� ��������� �� UPDATE, INSERT and DELETE ��������� </summary>
	CDBPropSet GetRowsetPropertiesSet() { return m_oDBDatabaseRowsetPropertiesSet; }
    /// <summary>����� data source �����</summary>
	CDataSource& GetDataSource() { return m_oDataSource; }

    /// <summary>������� ���� ����������</summary>
    void BeginTransaction();
    /// <summary>�������� �������� ����������</summary>
	void CommitTransaction();
    /// <summary>�������� �������� ����������</summary>
    void RollbackTransaction();

private:
    /// <summary> �������� ����������� �� ������ </summary>
    void InitializeConnectionProperties();
    /// <summary> �������� ����������� �� UPDATE, INSERT � DELETE ��������� </summary>
    void InitializeRowsetProperties();

// Members
// ----------------
private:
    CSession m_oCurrentSession;
    CDBPropSet m_oDBDatabaseConnectionPropertiesSet;
    CDBPropSet m_oDBDatabaseRowsetPropertiesSet;
    CDataSource m_oDataSource;
    bool m_propsInitialized = false;
    bool m_sessionIsOpen = false;

    CDatabaseConnection(const CDatabaseConnection&) = delete;
    CDatabaseConnection& operator=(const CDatabaseConnection&) = delete;
};

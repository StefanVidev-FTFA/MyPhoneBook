#pragma once

#include "pch.h"
#include <atlbase.h>
#include <atlcom.h>
#include "SmartArray.h"
#include <iostream>
#include <atldbcli.h>
#include <afxwin.h>
#include "DatabaseConnection.h"
#include "Macros.h"
#include "CommonMethods.h"
#include "PhoneNumbersAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CBaseTable

#define SELECT_ALL _T("SELECT * FROM %s WITH(NOLOCK)")
#define SELECT_BY_ID _T("SELECT * FROM %s WHERE ID = '%ld'")// need to fix the name here
#define SELECT_TOP_0 _T("SELECT TOP 0 * FROM %s")
#define SELECT_WHERE _T("SELECT * FROM %s WITH(UPDLOCK) WHERE ID ='%ld'")

template <typename tableType,typename accessorType>
class CBaseTable : public CCommand<CAccessor<accessorType>>
{
public:

    CBaseTable();

    bool SelectAll(CSmartArray<tableType>& oTableItemsArray);

    bool SelectWhereID(const long lID, tableType& recItem);

    bool Insert(const tableType& recItem);

    bool DeleteWhereId(const long lId);

    bool UpdateById(const int nId, const tableType& recItem);
};

template <typename tableType, typename accessorType>
inline CBaseTable<tableType, accessorType>::CBaseTable()
{
    CDatabaseConnection::GetInstance().OpenSession();
}

template <typename tableType, typename accessorType>
inline bool CBaseTable<tableType, accessorType>::SelectAll(CSmartArray<tableType>& oTableItemsArray)
{

    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString type = Utils::GetTableName<tableType>();
    CString strQuery = Utils::QueryWithStr(SELECT_ALL, type);

    HRESULT hResult = Open(oSession, strQuery);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Error executing query. Error: %ld. Query: %s"), hResult, strQuery);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();
        return false;
    }

    while (MoveNext() == S_OK)
    {
        oTableItemsArray.Add(new tableType(m_recItem));
    }

    Close();
    return true;
}

template <typename tableType, typename accessorType>
inline bool CBaseTable<tableType, accessorType>::SelectWhereID(const long lID, tableType& recItem)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString type = Utils::GetTableName<tableType>();
    CString strQuery;

    strQuery.Format(SELECT_BY_ID, type, lID);

    HRESULT hResult = Open(oSession, strQuery);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Error executing query. Error: %ld. Query: %s"), hResult, strQuery);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();
        return false;
    }

    if (MoveFirst() != S_OK)
    {
        CString strError;
        strError.Format(_T("Query has not found a result. Error: %ld. Query: %s"), hResult, strQuery);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();
        return false;
    }
    else
    {
        recItem = m_recItem;
    }

    Close();
    return true;
}

template <typename tableType, typename accessorType>
inline bool CBaseTable<tableType, accessorType>::Insert(const tableType& recItem)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString type = Utils::GetTableName<tableType>();
    CString strQuery = Utils::QueryWithStr(SELECT_TOP_0, type);

    HRESULT hResult = Open(oSession, strQuery, &CDatabaseConnection::GetInstance().GetRowsetPropertiesSet());
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Error executing query. Error: %ld ."), hResult);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();

        return false;
    }

    m_recItem = recItem;

    hResult = __super::Insert(1, true);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to Insert the data. Error: %ld"), hResult);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();
        return false;
    }

    Close();
    return true;
}

template <typename tableType, typename accessorType>
inline bool CBaseTable<tableType, accessorType>::DeleteWhereId(const long lId)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString type = Utils::GetTableName<tableType>();
    CString strQuery;

    strQuery.Format(SELECT_WHERE,type, lId);

    HRESULT hResult = Open(oSession, strQuery, &CDatabaseConnection::GetInstance().GetRowsetPropertiesSet());
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Error executing query. Error: %ld ."), hResult);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();

        return false;
    }

    MoveFirst();

    hResult = Delete();
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to execute Delete(). Error: %ld ."), hResult);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();

        return false;
    }

    Close();
    return true;
}

template <typename tableType, typename accessorType>
inline bool CBaseTable<tableType, accessorType>::UpdateById(const int nId, const tableType& recItem)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString type = Utils::GetTableName<tableType>();
    CString strQuery;

    strQuery.Format(SELECT_WHERE, type, nId);

    HRESULT hResult = Open(oSession, strQuery, &CDatabaseConnection::GetInstance().GetRowsetPropertiesSet());
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to open session for an update.Error: %ld"), hResult);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();

        return FALSE;
    }

    hResult = MoveFirst();
    if (FAILED(hResult))
    {
        AfxMessageBox(_T("Failed to execute MoveFirst(). Error: %d."), hResult);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();
        return false;
    }

    m_recItem = recItem;

    if (m_recItem.nUpdateCounter != recItem.nUpdateCounter)
    {
        CString strError;
        AfxMessageBox(_T("Failed to update the database! Update counter miss-match!"));

        Close();
        CDatabaseConnection::GetInstance().CloseSession();
        return false;
    }

    m_recItem.nUpdateCounter++;

    hResult = SetData(1);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to update the record in the database -> Error: %ld"), hResult);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();
        return false;
    }

    Close();
    return true;
}

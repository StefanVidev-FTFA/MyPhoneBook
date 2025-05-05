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

#define SELECT_ALL _T("SELECT * FROM %s WITH(NOLOCK)")
#define SELECT_BY_ID _T("SELECT * FROM %s WHERE ID = '%ld'")
#define SELECT_TOP_0 _T("SELECT TOP 0 * FROM %s")
#define SELECT_WHERE _T("SELECT * FROM %s WITH(UPDLOCK) WHERE ID ='%ld'")

/////////////////////////////////////////////////////////////////////////////
// CBaseTable
/// <summary> Клас съдържащ обща логика споделена между различните таблици </summary>
template <typename TableType,typename accessorType>
class CBaseTable : public CCommand<CAccessor<accessorType>>
{
// Constructor / Destructor
// ----------------
public:
    CBaseTable();

// Methods
// ----------------
public:
    /// <summary> Пълни масив от конкретен тип записи от избрана таблица </summary>
    bool SelectAll(CSmartArray<TableType>& oTableItemsArray);
    /// <summary> Избира конкретен запис от базата данни възоснова на идентификатор </summary>
    bool SelectWhereID(const long lID, TableType& recItem);
    /// <summary> Въвежда нов запис в избрана таблица </summary>
    bool Insert(TableType& recItem);
    /// <summary> Трие запис от конкретна таблица </summary>
    bool DeleteWhereId(const long lId);
    /// <summary> Опреснява запис от конкретна таблица </summary>
    bool UpdateById(const int nId, const TableType& recItem);

};

template <typename TableType, typename accessorType>
inline CBaseTable<TableType, accessorType>::CBaseTable()
{
    CDatabaseConnection::GetInstance().OpenSession();
}

template <typename TableType, typename accessorType>
inline bool CBaseTable<TableType, accessorType>::SelectAll(CSmartArray<TableType>& oTableItemsArray)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString strQuery = CUtils::GetFinalQuery<TableType>(SELECT_ALL);

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
        oTableItemsArray.Add(new TableType(m_recItem));
    }

    Close();

    return true;
}

template <typename TableType, typename accessorType>
inline bool CBaseTable<TableType, accessorType>::SelectWhereID(const long lID, TableType& recItem)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString strQuery = CUtils::GetFinalQuery<TableType>(SELECT_BY_ID, lID);

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

template <typename TableType, typename accessorType>
inline bool CBaseTable<TableType, accessorType>::Insert(TableType& recItem)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString strQuery = CUtils::GetFinalQuery<TableType>(SELECT_TOP_0);

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

    hResult = MoveFirst();
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to MoveFirst(). Error: %ld"), hResult);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();
        return false;
    }

    recItem.nId = m_recItem.nId;

    Close();

    return true;
}

template <typename TableType, typename accessorType>
inline bool CBaseTable<TableType, accessorType>::DeleteWhereId(const long lId)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString strQuery = CUtils::GetFinalQuery<TableType>(SELECT_WHERE, lId);

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
    if (FAILED(hResult))
    {
        Close();
        return false;
    }

    hResult = Delete();
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("<>Failed to execute Delete(). Error: %ld ."), hResult);
        AfxMessageBox(strError);

        Close();
        CDatabaseConnection::GetInstance().CloseSession();

        return false;
    }

    Close();
    return true;
}

template <typename TableType, typename accessorType>
inline bool CBaseTable<TableType, accessorType>::UpdateById(const int nId, const TableType& recItem)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString strQuery= CUtils::GetFinalQuery<TableType>(SELECT_WHERE, nId);

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

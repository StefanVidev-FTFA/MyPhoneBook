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
#define SELECT_BY_ID _T("SELECT * FROM CITIES WHERE ID = '%ld'")
#define SELECT_TOP_0 _T("SELECT TOP 0 * FROM %s")

template <typename tableType,typename accessorType>
class CBaseTable : public CCommand<CAccessor<accessorType>>
{
public:
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray);

    bool SelectWhereID(const long lID, tableType& recItem);

    bool Insert(const tableType& recItem);
};

template <typename tableType, typename accessorType>
inline bool CBaseTable<tableType, accessorType>::SelectAll(CSmartArray<tableType>& oTableItemsArray)
{

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
        oSession.Close();
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

    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString strQuery;
    strQuery.Format(SELECT_BY_ID, lID);

    HRESULT hResult = Open(oSession, strQuery);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Error executing query. Error: %ld. Query: %s"), hResult, strQuery);
        AfxMessageBox(strError);

        Close();
        oSession.Close();
        return false;
    }

    if (MoveFirst() != S_OK)
    {
        CString strError;
        strError.Format(_T("Query has not found a result. Error: %ld. Query: %s"), hResult, strQuery);
        AfxMessageBox(strError);

        Close();
        oSession.Close();
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
        oSession.Close();

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
        oSession.Close();
        return false;
    }

    AfxMessageBox(_T("Successfully Inserted the new item"), MB_ICONINFORMATION);

    Close();
    return true;
}

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

template <typename tableType,typename accessorType>
class CBaseTable : public CCommand<CAccessor<accessorType>>
{
public:
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray);

};



template <typename tableType, typename accessorType>
inline bool CBaseTable<tableType, accessorType>::SelectAll(CSmartArray<tableType>& oTableItemsArray)
{


    CDataSource& oDataSource = CDatabaseConnection::GetInstance().GetDataSource();
    CSession oSession;

    // Отваряме сесия
    HRESULT  hResult = oSession.Open(oDataSource);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Unable to open session.Error: %ld"), hResult);
        AfxMessageBox(strError);

        return false;
    }

    CString type;
    if (typeid(tableType) == typeid(PHONE_NUMBERS)) 
    {
        type =  _T("PHONE_NUMBERS");
    }
    else if (typeid(tableType) == typeid(CITIES))
    {
        type = _T("CITIES");
    }

    CString strQuery = Utils::QueryWithStr(SELECT_ALL, type);



    hResult = Open(oSession, strQuery);
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
    oSession.Close();
    return true;
}
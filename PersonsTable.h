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
// CPersonsTable

/// <summary> Клас за работа с таблицата CITIES. </summary>
class CPersonsTable : public CCommand<CAccessor<CPhoneNumbersAccessor>>
{
    // Methods
    // ----------------
public:

    /// <summary>
    /// Избира всички записи от таблицата която е зададена като тип
    /// </summary>
    template <typename tableType>
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray)
    {
        
        if(typeid(tableType) == typeid(PHONE_NUMBERS))
        {
            AfxMessageBox(_T("its phone numbers"));
        }
        else if(typeid(tableType) == typeid(CITIES))
        {
            AfxMessageBox(_T("its the cities boiiii"));
        }


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

        CString strQuery =_T("SELECT * FROM PHONE_NUMBERS WITH(NOLOCK)");

        //strQuery.Format(_T("SELECT * FROM %s WITH(NOLOCK)"), strTableName);


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
            oTableItemsArray.Add(new tableType(m_recPhone));
        }

        Close();
        oSession.Close();
        return true;
    }
};
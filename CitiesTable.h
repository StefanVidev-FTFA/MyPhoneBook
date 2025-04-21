#pragma once
#include "pch.h"
#include "CitiesAccessor.h"
#include <atlbase.h>
#include <atlcom.h>
#include "CitiesArray.h"
#include "SmartArray.h"
#include "CitiesTable.h"
#include <iostream>
#include <atldbcli.h>
#include <afxwin.h>
#include "DatabaseConnection.h"
#include "Macros.h"
#include "CommonMethods.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary> Клас за работа с таблицата CITIES. </summary>
class CCitiesTable : public CCommand<CAccessor<CCitiesAccessor>>
{
// Methods
// ----------------
public://template <typename Ttable>

    /// <summary>
    /// Избира всички записи от таблицата която е зададена като тип
    /// </summary>
    template <typename tableType>
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray)
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

        // Конструираме заявката за извличане на всички градове
        CString strQuery = _T("SELECT * FROM CITIES WITH(NOLOCK)");


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
            oTableItemsArray.Add(new tableType(m_recCity));
        }

        Close();
        oSession.Close();
        return true;
    }
    /// <summary>
    /// Избира град възоснова на идентификационен номер.
    /// </summary>
    bool SelectWhereID(const long lID, CITIES& recCity);
    /// <summary>
    /// Модифицира град който отговарч на конкретен идентификационен номер.
    /// </summary>
    bool UpdateWhereID(const long lID,const CITIES& recCity);
    /// <summary>
	/// Въвежда нов град.
    /// </summary>
    bool Insert(const CITIES& recCity);
    /// <summary>
	/// ИЗтрива запис за град по идентификационен номер.
    /// </summary>
    bool DeleteWhereID(const long lID);
};
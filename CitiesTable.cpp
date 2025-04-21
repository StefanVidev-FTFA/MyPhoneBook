#include "pch.h"
#include "CitiesTable.h"
#include <iostream>
#include <atldbcli.h>
#include "CitiesArray.h"
#include <afxwin.h>
#include "DatabaseConnection.h"
#include "Macros.h"
#include "CommonMethods.h"
#include "SmartArray.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable


// Methods
// ----------------

bool CCitiesTable::SelectWhereID(const long lID, CITIES& recCity)
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

    // Конструираме заявката за избора на град възоснова на идентификационен номер.
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = '%ld'"), lID);



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
        recCity = m_recCity;
    }

    Close();
    oSession.Close();

    return true;
}

bool CCitiesTable::UpdateWhereID(const long lID, const CITIES& recCity)
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

    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WITH(UPDLOCK) WHERE ID = '%ld'"), lID);

    hResult = Open(oSession, strQuery, &CDatabaseConnection::GetInstance().GetRowsetPropertiesSet());
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to open session for an update.Error: %ld"), hResult);
        AfxMessageBox(strError);

        Close();
        oSession.Close();

        return FALSE;
    }

    hResult = MoveFirst();
    if (FAILED(hResult))
    {
        AfxMessageBox(_T("Failed to execute MoveFirst(). Error: %d."), hResult);

        Close();
        oSession.Close();
        return false;
    }

    m_recCity = recCity;

    if (m_recCity.nUpdateCounter != recCity.nUpdateCounter)
    {
        CString strError;
        AfxMessageBox(_T("Failed to update the database! Update counter miss-match!"));
        oSession.Close();
        return false;
    }

    m_recCity.nUpdateCounter++;

    hResult = SetData(1);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to update the record in the database -> Error: %ld"), hResult);
        AfxMessageBox(strError);

        Close();
        oSession.Close();
        return false;
    }
    MESSAGE_INFO(_T("Successfully updated the city"));

    Close();
    oSession.Close();
    return true;
}

bool CCitiesTable::Insert(const CITIES& recCity)
{
    CDataSource& oDataSource = CDatabaseConnection::GetInstance().GetDataSource();
    CSession oSession;

    HRESULT  hResult = oSession.Open(oDataSource);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Unable to open session.Error: %ld"), hResult);
        AfxMessageBox(strError);

        return false;
    }

    hResult = Open(oSession, _T("SELECT TOP 0 * FROM CITIES"), &CDatabaseConnection::GetInstance().GetRowsetPropertiesSet());
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Error executing query. Error: %ld ."), hResult);
        AfxMessageBox(strError);

        Close();
        oSession.Close();

        return false;
    }

    m_recCity = recCity;

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

    AfxMessageBox(_T("Successfully Inserted the new city"), MB_ICONINFORMATION);

    Close();
    oSession.Close();
    return true;
}

bool CCitiesTable::DeleteWhereID(const long lID)
{
    CDataSource& oDataSource = CDatabaseConnection::GetInstance().GetDataSource();
    CSession oSession;

    HRESULT  hResult = oSession.Open(oDataSource);
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Unable to open session.Error: %ld"), hResult);
        AfxMessageBox(strError);
        return false;
    }

    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WITH(UPDLOCK) WHERE ID ='%ld'"), lID);

    hResult = Open(oSession, strQuery, &CDatabaseConnection::GetInstance().GetRowsetPropertiesSet());
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Error executing query. Error: %ld ."), hResult);
        AfxMessageBox(strError);

        Close();
        oSession.Close();

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
        oSession.Close();

        return false;
    }

    CString strNotidy;
    strNotidy.Format(_T("Successfully deleted row with id:  %ld"), lID);
    MESSAGE_INFO(strNotidy);


    Close();
    oSession.Close();
    return true;
}
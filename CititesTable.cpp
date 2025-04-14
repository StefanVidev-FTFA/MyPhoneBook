#include "pch.h"
#include "CitiesTable.h"
#include <iostream>
#include <atldbcli.h>
#include "CitiesArray.h"
#include <afxwin.h>
#include "DatabaseConnection.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable


// Methods
// ----------------
bool CCitiesTable::SelectAll(CCitiesArray& oCitiesArray)
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

        oDataSource.Close();
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
         oCitiesArray.Add(new CITIES(m_recCity));

    }

    Close();
    oSession.Close();
    return true;
}

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

	oSession.Close();

    return true;
}

bool CCitiesTable::UpdateWhereID(const long lID,CITIES& recCity)
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

        oSession.Close();
        oDataSource.Close();

        return FALSE;
    }
    hResult = MoveFirst();
	//CITIES recInitialCityInfo = m_recCity;

    if (FAILED(hResult))
    {
        AfxMessageBox(_T("Error opening record. Error: %d."), hResult);

        oSession.Close();
        return false;
    }
    strncpy_s(m_recCity.szCityName, "Svilengrad", MAX_CITY_NAME - 1);

    //if (m_recCity.nUpdateCounter != recInitialCityInfo.nUpdateCounter) 
    //{
    //    CString strError;
    //    AfxMessageBox(_T("Failed to update the database! Update counter miss-match!"));
    //    oSession.Close();
    //    return false;
    //}

	m_recCity.nUpdateCounter++;
    hResult = SetData(1);

    hResult = Update();
    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to update the database   Error: %ld"), hResult);
        AfxMessageBox(strError);

        oSession.Close();
        return false;
    }

    CString strNotify;
    strNotify.Format(_T("Successfully updated city with ID: %ld"), lID);
    AfxMessageBox(strNotify, MB_ICONINFORMATION);

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

    hResult = Open(oSession, _T("SELECT * FROM CITIES"), &CDatabaseConnection::GetInstance().GetRowsetPropertiesSet());


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


    hResult = __super::Insert(1,true);

    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to Insert the data. Error: %ld"), hResult);
        AfxMessageBox(strError);

        Close();
        oSession.Close();
        return false;
    }

    hResult = Update();

    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to Update() the data. Error: %ld"), hResult);
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

    hResult = Update();

    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Failed to execute Update(). Error: %ld ."), hResult);
        AfxMessageBox(strError);

        Close();
        oSession.Close();

        return false;
    }

    CString strNotidy;
    strNotidy.Format(_T("Successfully deleted row with id:  %ld"), lID);
    AfxMessageBox(strNotidy, MB_ICONINFORMATION);


    Close();
    oSession.Close();
    return true;
}
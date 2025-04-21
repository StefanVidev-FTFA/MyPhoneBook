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

/// <summary> ���� �� ������ � ��������� CITIES. </summary>
class CCitiesTable : public CCommand<CAccessor<CCitiesAccessor>>
{
// Methods
// ----------------
public://template <typename Ttable>

    /// <summary>
    /// ������ ������ ������ �� ��������� ����� � �������� ���� ���
    /// </summary>
    template <typename tableType>
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray)
    {
        CDataSource& oDataSource = CDatabaseConnection::GetInstance().GetDataSource();
        CSession oSession;

        // �������� �����
        HRESULT  hResult = oSession.Open(oDataSource);
        if (FAILED(hResult))
        {
            CString strError;
            strError.Format(_T("Unable to open session.Error: %ld"), hResult);
            AfxMessageBox(strError);

            return false;
        }

        // ������������ �������� �� ��������� �� ������ �������
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
    /// ������ ���� ��������� �� ���������������� �����.
    /// </summary>
    bool SelectWhereID(const long lID, CITIES& recCity);
    /// <summary>
    /// ���������� ���� ����� �������� �� ��������� ���������������� �����.
    /// </summary>
    bool UpdateWhereID(const long lID,const CITIES& recCity);
    /// <summary>
	/// ������� ��� ����.
    /// </summary>
    bool Insert(const CITIES& recCity);
    /// <summary>
	/// ������� ����� �� ���� �� ���������������� �����.
    /// </summary>
    bool DeleteWhereID(const long lID);
};
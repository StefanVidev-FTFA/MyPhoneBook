#include "pch.h"
#include "CitiesTable.h"
#include <vector>


using namespace std;

bool CCitiesTable::AssignAllCityIds(CStringList& cityIdsList)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString type = Utils::GetTableName<CITIES>();
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
        CString strId;
        strId.Format(_T("%d"), m_recItem.nId);
        cityIdsList.AddTail(strId);
    }

    Close();
    return true;
}
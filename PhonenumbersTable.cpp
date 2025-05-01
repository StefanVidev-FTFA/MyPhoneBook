#include "pch.h"
#include "PhoneNumbersTable.h"




bool CPhoneNumbersTable::GetPersonsPhoneNumbers(CSmartArray<PHONE_NUMBERS>& oItemsArray, long lId)
{
    CDatabaseConnection::GetInstance().OpenSession();
    CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

    CString strQuery;

    strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS WHERE PERSON_ID = '%ld';"), lId);

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
        oItemsArray.Add(new PHONE_NUMBERS(m_recItem));
    }

    Close();
    return true;
}
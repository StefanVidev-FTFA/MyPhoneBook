#pragma once
#include "pch.h"
#include "PersonsTable.h"
#include "TempCitiesTable.h"
#include "PhoneNumbersTable.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CPersonsData

/// <summary> Клас служещ за изпълнението на бизнес логиката на указателя /// </summary>
class CPersonsData
{
private:
    // Constants
    // ----------------
    CPhoneNumbersTable m_oPhoneNumbersTable;
    CTempCitiesTable m_oCitiesTable;


    // Methods
    // ----------------
public:

    template <typename tableType>
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray)
    {
        if constexpr (is_same_v<tableType, PHONE_NUMBERS>)
        {
            return m_oPhoneNumbersTable.SelectAll(oTableItemsArray);
        }
        else if constexpr (is_same_v<tableType, CITIES>)
        {
            return m_oCitiesTable.SelectAll(oTableItemsArray);
        }
        else
        {
            return false;
        }
    }
};
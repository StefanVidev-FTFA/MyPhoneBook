#pragma once
#include "pch.h"
#include "PersonsTable.h"
#include "CitiesTable.h"
#include "PhoneNumbersTable.h"
#include "PhoneTypesTable.h"

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
    CCitiesTable m_oCitiesTable;
    CPersonsTable m_oPersonsTable;
    CPhoneTypesTable m_oPhoneTypesTable;


    // Methods
    // ----------------
public:

    template <typename tableType>
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray)
    {
        CDatabaseConnection::GetInstance().OpenSession();

        if constexpr (is_same_v<tableType, PHONE_NUMBERS>)
        {
            return m_oPhoneNumbersTable.SelectAll(oTableItemsArray);
        }
        else if constexpr (is_same_v<tableType, CITIES>)
        {
            return m_oCitiesTable.SelectAll(oTableItemsArray);
        }
        else if constexpr (is_same_v<tableType, PERSONS>)
        {
            return m_oPersonsTable.SelectAll(oTableItemsArray);
        }
        else if constexpr (is_same_v<tableType, PHONE_TYPES>)
        {
            return m_oPhoneTypesTable.SelectAll(oTableItemsArray);
        }
        else
        {
            return false;
        }
    }
};
#pragma once
#include "pch.h"
#include "PersonsTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

/// <summary> Клас служещ за изпълнението на бизнес логиката на указателя /// </summary>
class CPersonsData
{
private:
    // Constants
    // ----------------
    CPersonsTable m_oPersonsTable;
    CCitiesTable m_oCitiesTable;


    // Methods
    // ----------------
public:

    template <typename tableType>
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray)
    {
        //if constexpr (std::is_same_v<tableType, PHONE_NUMBERS>) {
        if (typeid(tableType) == typeid(PHONE_NUMBERS))
        {
            return m_oPersonsTable.SelectAll(oTableItemsArray);
        }
        else if(typeid(tableType) == typeid(CITIES))
        {
            return m_oPersonsTable.SelectAll(oTableItemsArray);
        }
    }
};
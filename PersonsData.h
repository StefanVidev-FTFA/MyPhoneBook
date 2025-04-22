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


    // Methods
    // ----------------
public:
    /// <summary> Чете всеки запис от конкретна таблицата в sql и ги въвежда във масив от записи. </summary>
    template <typename tableType>
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray)
    {
        return m_oPersonsTable.SelectAll(oTableItemsArray);
    }
};
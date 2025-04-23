#pragma once
#include "pch.h"
#include "PersonsTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

/// <summary> ���� ������ �� ������������ �� ������ �������� �� ��������� /// </summary>
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
        return m_oPersonsTable.SelectAll(oTableItemsArray);
    }
};
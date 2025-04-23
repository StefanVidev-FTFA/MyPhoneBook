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


    // Methods
    // ----------------
public:

    bool SelectAll(CSmartArray<PHONE_NUMBERS>& oTableItemsArray)
    {
        return m_oPersonsTable.SelectAll(oTableItemsArray);
    }
};
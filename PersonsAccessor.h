#pragma once

#include "Persons.h"
#include <atldbcli.h>
#include "BaseAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsAccessor

class CPersonsAccessor : public CBaseAccessor<PERSONS>
{
protected:

    BEGIN_ACCESSOR_MAP(CPersonsAccessor, 2)
        BEGIN_ACCESSOR(0, true)
            COLUMN_ENTRY(1, m_recItem.nId)
        END_ACCESSOR()

        BEGIN_ACCESSOR(1, true)
            COLUMN_ENTRY(2, m_recItem.nUpdateCounter)
            COLUMN_ENTRY(3, m_recItem.szFirstName)
            COLUMN_ENTRY(4, m_recItem.szMiddleName)
            COLUMN_ENTRY(5, m_recItem.szLastName)
            COLUMN_ENTRY(6, m_recItem.szEgn)
            COLUMN_ENTRY(7, m_recItem.nCityId)
            COLUMN_ENTRY(8, m_recItem.szAddress)
        END_ACCESSOR()
    END_ACCESSOR_MAP()
};

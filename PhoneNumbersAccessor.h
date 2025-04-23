#pragma once
#include "Cities.h"
#include <atldbcli.h>
#include "PhoneNumbers.h"
#include "BaseAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersAccessor

class CPhoneNumbersAccessor : public CBaseAccessor<PHONE_NUMBERS>
{
protected:

    BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)
        BEGIN_ACCESSOR(0, true)
            COLUMN_ENTRY(1, m_recItem.nId)
        END_ACCESSOR()

        BEGIN_ACCESSOR(1, true)
            COLUMN_ENTRY(2, m_recItem.nUpdateCounter)
            COLUMN_ENTRY(3, m_recItem.nPersonId)
            COLUMN_ENTRY(4, m_recItem.nPhoneTypeId)
            COLUMN_ENTRY(5, m_recItem.szPhoneNumber)
        END_ACCESSOR()

    END_ACCESSOR_MAP()
};
#pragma once
#include "Cities.h"
#include <atldbcli.h>
#include "PhoneNumbers.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersAccessor

class CPhoneNumbersAccessor
{
protected:
    PHONE_NUMBERS m_recPhone;

    BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)
        BEGIN_ACCESSOR(0, true)
            COLUMN_ENTRY(1, m_recPhone.nId)
        END_ACCESSOR()

        BEGIN_ACCESSOR(1, true)
            COLUMN_ENTRY(2, m_recPhone.nUpdateCounter)
            COLUMN_ENTRY(3, m_recPhone.nPersonId)
            COLUMN_ENTRY(4, m_recPhone.nPhoneTypeId)
            COLUMN_ENTRY(5, m_recPhone.szPhoneNumber)
        END_ACCESSOR()

    END_ACCESSOR_MAP()
};
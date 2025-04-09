#pragma once
#include "Cities.h"
#include <atldbcli.h>

/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor


class CCitiesAccessor
{
protected:
    CITIES m_recCity;
    
    BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
        BEGIN_ACCESSOR(0, true)
            COLUMN_ENTRY(1, m_recCity.nId)
        END_ACCESSOR()

        BEGIN_ACCESSOR(1, true)
            COLUMN_ENTRY(2, m_recCity.nUpdateCounter)
            COLUMN_ENTRY(3, m_recCity.szCityName)
            COLUMN_ENTRY(4, m_recCity.szRegion)
        END_ACCESSOR()
    END_ACCESSOR_MAP()
};
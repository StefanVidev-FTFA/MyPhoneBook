#pragma once
#include "Cities.h"
#include <atldbcli.h>
#include "BaseAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor
class CCitiesAccessor : public CBaseAccessor<CITIES>
{
protected:
    
    BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
        BEGIN_ACCESSOR(0, true)
            COLUMN_ENTRY(1, m_recItem.nId)
        END_ACCESSOR()

        BEGIN_ACCESSOR(1, true)
            COLUMN_ENTRY(2, m_recItem.nUpdateCounter)
            COLUMN_ENTRY(3, m_recItem.szCityName)
            COLUMN_ENTRY(4, m_recItem.szRegion)
        END_ACCESSOR()
    END_ACCESSOR_MAP()
};
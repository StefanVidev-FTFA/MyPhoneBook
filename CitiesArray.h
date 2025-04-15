#pragma once

#include <afx.h>
#include "Cities.h"
#include "afxcoll.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesArray

/// <summary> Клас който дефинира масив от записи на таблицата CITIES. /// </summary>
class CCitiesArray : public CPtrArray
{
// Constructor / Destructor
// ----------------     
public:
    CCitiesArray() {}
    virtual ~CCitiesArray() 
    {
        if(!IsEmpty())
        {
            for (int i = 0; i < GetSize(); i++)
            {
                delete static_cast<CITIES*>(GetAt(i));
            }
        }
    }
};
